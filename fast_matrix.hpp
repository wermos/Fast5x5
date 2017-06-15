#include<iostream>
#include<cstring>
#include<array>

#include<boost/simd/pack.hpp>
#include<boost/simd/constant/zero.hpp>
#include<boost/simd/constant/one.hpp>
#include<boost/simd/function/aligned_store.hpp>
#include<boost/simd/function/dot.hpp>
#include<boost/simd/function/shuffle.hpp>
#include<boost/simd/function/none.hpp>

namespace bs = boost::simd;

constexpr int nearest_power_of_two(int min_value, int current_value) {
    // Computes the nearest power of two relative to `min_value` starting from the power of two `current_value`
    return min_value > current_value/2 ? current_value : nearest_power_of_two(min_value, current_value/2);
}


template <typename T, int NRows, int NCols, int MaxVecSize>
class BaseMatrix;

/*
template <typename T, int MatrixSize, int MaxVecSize>
class IdentityMatrix;

template<typename T, int MatrixSize, int MaxVecSize>
class Matrix: public BaseMatrix<T, MatrixSize, MaxVecSize> {
};

template<typename T, int MatrixSize, int MaxVecSize>
class TransposedMatrix: public BaseMatrix<T, MatrixSize, MaxVecSize> {};

template <typename T, int MatrixSize, int MaxVecSize>
TransposedMatrix<T, MatrixSize, MaxVecSize> transpose(Matrix<T, MatrixSize, MaxVecSize> &m) {
    return static_cast<TransposedMatrix<T, MatrixSize, MaxVecSize>>(m);
}


template <typename T, int MatrixSize, int MaxVecSize>
Matrix<T, MatrixSize, MaxVecSize> transpose(TransposedMatrix<T, MatrixSize, MaxVecSize> &m) {
    return static_cast<Matrix<T, MatrixSize, MaxVecSize>>(m);
}
*/
template <typename T, int NRows, int NCols, int MaxVecSize>
std::ostream & operator<<(std::ostream &os, BaseMatrix<T, NRows, NCols, MaxVecSize> &mat) {
// Matrix printing function
    for (int i=0; i<NRows; i++) {
        for (int j=0; j<NCols; j++) {
            os << mat.array[i*BaseMatrix<T, NRows, NCols, MaxVecSize>::VecSize + j] << ", ";
        }
        os << std::endl;
    }
    return os;
}

template <typename M>
static inline void matrix_add(M &a, M &b, M &c) {
    using pack_t = typename M::pack_t;
    for (int i=0; i<M::NRows; i++) {
        int index = M::VecSize*i;
        pack_t row_a(&a.array[index]), row_b(&b.array[index]);
        bs::aligned_store(row_a + row_b, &c.array[index]);
    }
}

template <typename M>
static inline void matrix_sub(M &a, M &b, M &c) {
    using pack_t = typename M::pack_t;
    for (int i=0; i<M::NRows; i++) {
        int index = M::VecSize*i;
        pack_t row_a(&a.array[index]), row_b(&b.array[index]);
        bs::aligned_store(row_a - row_b, &c.array[index]);
    }
}

template <typename T, int l, int m, int n, int MVS>
static inline void matrix_mul_m_m(BaseMatrix<T, l, m, MVS> &a, BaseMatrix<T, m, n, MVS> &b, BaseMatrix<T, l, n, MVS> &c) {
/*
 * Computes the following matrix product C = A*B
 * where A, B and C are BaseMatrix objects.
 * The idea is that we can perform the costly reduction for all the elements in a row
 * of C in one vector.
 * This use only vector operations so the compiler can optimize easily.
 */
    static constexpr int LeftVecSize = BaseMatrix<T, l, m, MVS>::VecSize;
    static constexpr int RightVecSize = BaseMatrix<T, m, n, MVS>::VecSize;
    using pack_t = bs::pack<T, RightVecSize>;
    /* Algorithm:
     * For each row of C matrix:
     *  * Load one element of A and broadcast it into vector.
     *  * Load the corresponding row of B into vector.
     *  * Computes element-wise product between these two vector.
     *  * Repeat for each element of A in the row and sum these results.
     *  * Store the sommation as corresponding row of C.
     */
    for (int i=0; i<l; i++) {
        pack_t res = bs::Zero<pack_t>();
        for (int j=0; j<m; j++) {
            pack_t factor {a.array[LeftVecSize*i + j]};
            pack_t row(&b.array[RightVecSize*j]);
            res += factor * row;
        }
        bs::aligned_store(res, &c.array[RightVecSize*i]);
    }
}

template <typename T, int l, int m, int n, int MVS>
static inline void matrix_mul_mt_m(BaseMatrix<T, m, l, MVS> &a, BaseMatrix<T, m, n, MVS> &b, BaseMatrix<T, l, n, MVS> &c) {
/*
 * Computes the following matrix product C = t(A)*B
 * where A, B and C are BaseMatrix objects.
 * This code is nearly identical to matrix_mul_m_m but we
 * run through A in column instead of row
 */
    static constexpr int LeftVecSize = BaseMatrix<T, m, l, MVS>::VecSize;
    static constexpr int RightVecSize = BaseMatrix<T, m, n, MVS>::VecSize;
    using pack_t = bs::pack<T, RightVecSize>;
    for (int i=0; i<l; i++) {
        pack_t res = bs::Zero<pack_t>();
        for (int j=0; j<m; j++) {
            pack_t factor {a.array[LeftVecSize*j + i]};
            pack_t row(&b.array[RightVecSize*j]);
            res += factor * row;
        }
        bs::aligned_store(res, &c.array[RightVecSize*i]);
    }
}

template <typename T, int l, int m, int n, int MVS>
static inline void matrix_mul_m_mt(BaseMatrix<T, l, m, MVS> &a, BaseMatrix<T, n, m, MVS> &b, BaseMatrix<T, l, n, MVS> &c) {
/*
 * Computes the following matrix product C = A*t(B)
 * where A, B and C are BaseMatrix objects.
 * This is slower than A*B product due to mandatory reduction.
 * The idea is that we don't need to transpose B beforehand. Since we have
 * to load columns of t(B) into vector register we can load row of B instead.
 * Assuming that B is store in row order, row of B are correctly aligned for loading.
 */
    static constexpr int VecSize = BaseMatrix<T, l, m, MVS>::VecSize; //VecSize are the same for left and right matrices 
    static constexpr int ResVecSize = BaseMatrix<T, l, n, MVS>::VecSize;
    using pack_t = bs::pack<T, VecSize>;
    /* Algorithm:
     * For each C matrix element:
     *  * Load corresponding row of A into vector.
     *  * Load corresponding column of t(B) => Load corresponding row of B into vector.
     *  * Computes dot product between the two vector.
     *  * Store the resulting scalar of C.
     */
    for (int i=0; i<l; i++) {
        pack_t row(&a.array[VecSize*i]);
        for (int j=0; j<n; j++) {
            pack_t row_transpose(&b.array[VecSize*j]);
            // Dot is a slow operation but it will get better with newer hardware.
            c.array[ResVecSize*i + j] = bs::dot(row, row_transpose);
        }
    }
}

template <typename T, int NumberRows, int NumberCols, int MaximumVectorSize>
class Inverse {
    using M = BaseMatrix<T, NumberRows, NumberCols, MaximumVectorSize>;
    public:
    static void inverse(M &a, M &inv) {
        /* Computes inverse of `a` by using Cholesky decomposition.
         * M must be symmetric, positive-definite.
         * a = t(r)*r, where r is upper triangular.
         * a^-1 = (r^-1)*t(r^-1) = inv
         */
        M r;
        using pack_t = typename M::pack_t;

        // Cholesky decomposition
        for (int i=0; i<M::NRows; i++) {
            pack_t sum_row = bs::Zero<pack_t>();

            for (int j=0; j<i; j++) {
                pack_t cur_row(&r.array[j*M::VecSize]);
                pack_t factor {r.array[j*M::VecSize+i]};
                sum_row += cur_row*factor;
            }

            pack_t res_row(&a.array[i*M::VecSize]);
            res_row -= sum_row;
            pack_t diviser {1/std::sqrt(res_row[i])};
            res_row *= diviser;
            bs::aligned_store(res_row, &r.array[i*M::VecSize]);
        }

        M inv_r;
        static M Id(1);
        // Inversion of R by backward substitution
        for (int i=(M::NRows-1); i>=0; i--) {
            pack_t sum_row = bs::Zero<pack_t>();

            for (int j=(M::NRows-1); j > i; j--) {
                pack_t cur_row(&inv_r.array[j*M::VecSize]);
                pack_t factor {r.array[i*M::VecSize+j]};
                sum_row += cur_row*factor;
            }

            pack_t res_row(&Id.array[i*M::VecSize]);
            res_row -= sum_row;
            pack_t diviser {1/r.array[i*M::VecSize+i]};
            res_row *= diviser;
            bs::aligned_store(res_row, &inv_r.array[i*M::VecSize]);
        }


        // Compute inverse of initial matrix
        /* TODO: Since inv_r is a triangular matrix there is room
         * for optimisation on this product
         */ 
        matrix_mul_m_mt(inv_r, inv_r, inv);
    }
};

template <typename T, int MaximumVectorSize>
class Inverse<T, 2, 2, MaximumVectorSize> {
    using M = BaseMatrix<T, 2, 2, MaximumVectorSize>;
    public:
    static void inverse(M &a, M &inv) {
        T inv_det = 1/(a.array[0]*a.array[M::VecSize + 1]- a.array[1]*a.array[1]);
        inv.array[0] = inv_det*a.array[M::VecSize + 1];
        inv.array[1] = inv.array[M::VecSize] = -inv_det*a.array[1];
        inv.array[M::VecSize + 1] = inv_det*a.array[0];
    }
};

template <typename T, int NumberRows, int NumberCols, int MaximumVectorSize>
class BaseMatrix {
/* Class for matrix object
 * Matrix object are linearized 2D array with padded line to fit vector size
 */
    static_assert(NumberCols <= MaximumVectorSize, "Matrix width must be less than maximum vector size");
    static_assert((MaximumVectorSize >= 4) & !(MaximumVectorSize & (MaximumVectorSize - 1)), "Maximum vector size must be a power of two.");

    protected:
    static constexpr int MaxVecSize = MaximumVectorSize;
    // We use the smallest vector size possible
    static constexpr int VecSize = nearest_power_of_two(NumberCols, MaximumVectorSize);

    using matrix_t = BaseMatrix<T, NumberRows, NumberCols, MaximumVectorSize>;
    using pack_t = bs::pack<T, VecSize>;
    using ElementType = T;

    public:
    static constexpr int NRows = NumberRows;
    static constexpr int NCols = NumberCols;

    BaseMatrix() = default;
    BaseMatrix(T const a[]) {
        if (NCols == VecSize) { // In this case there is no padding, we can copy directly the array
            std::memcpy(this->array, a, sizeof(T)*NRows*VecSize);
        }
        else {
            for (int i=0; i<NRows; i++) {
                // In this case we copy data row by row
                std::memcpy(&this->array[i*VecSize], &a[i*NCols], sizeof(T)*NCols);
            }
        }
    }

    BaseMatrix(T const a) {
        for (int i=0; i<NRows; i++) {
            array[VecSize*i+i] = a;
        }
    }

    matrix_t operator=(T const a[]) {
        if (NCols == VecSize) { // In this case there is no padding, we can copy directly the array
            std::memcpy(this->array, a, sizeof(T)*NRows*VecSize);
        }
        else {
            for (int i=0; i<NRows; i++) {
                // In this case we copy data row by row
                std::memcpy(&this->array[i*VecSize], &a[i*NCols], sizeof(T)*NCols);
            }
        }
        return *this;
    }
    matrix_t operator=(matrix_t &other) {
        std::memcpy(this->array, other.array, sizeof(T)*NRows*VecSize);
        return *this;
    }

    std::array<ElementType, NRows*NCols> dump_array() const {
        std::array<ElementType, NRows*NCols> returned_array;
        if (NCols == VecSize) { // In this case there is no padding, we can copy directly the array
            std::memcpy(&returned_array[0], this->array, sizeof(T)*NRows*VecSize);
        }
        else {
            for (int i=0; i<NRows; i++) {
                std::memcpy(&returned_array[i*NCols], &this->array[i*VecSize], sizeof(T)*NCols);
            }
        }
        return returned_array;
    }


    private:
    friend void matrix_add<matrix_t>(matrix_t &a, matrix_t &b, matrix_t &c);
    friend void matrix_sub<matrix_t>(matrix_t &a, matrix_t &b, matrix_t &c);
    template <typename U, int l, int m, int n, int MVS> friend void matrix_mul_m_m(BaseMatrix<U, l, m, MVS> &a, BaseMatrix<U, m, n, MVS> &b, BaseMatrix<U, l, n, MVS> &c);
    template <typename U, int l, int m, int n, int MVS> friend void matrix_mul_mt_m(BaseMatrix<U, m, l, MVS> &a, BaseMatrix<U, m, n, MVS> &b, BaseMatrix<U, l, n, MVS> &c);
    template <typename U, int l, int m, int n, int MVS> friend void matrix_mul_m_mt(BaseMatrix<U, l, m, MVS> &a, BaseMatrix<U, n, m, MVS> &b, BaseMatrix<U, l, n, MVS> &c);
    friend class Inverse<T, NRows, NCols, MaxVecSize>;
    friend std::ostream & operator<<<T, NRows, NCols, MaxVecSize>(std::ostream &os, matrix_t &mat);

    protected:
    alignas(sizeof(T)*VecSize) T array[NRows*VecSize] = {0};

};
