#include<iostream>
#include<cstring>

#include<boost/simd/pack.hpp>
#include<boost/simd/constant/zero.hpp>
#include<boost/simd/function/aligned_store.hpp>
#include<boost/simd/function/dot.hpp>

namespace bs = boost::simd;

constexpr int nearest_power_of_two(int min_value, int current_value) {
    // Computes the nearest power of two relative to `min_value` starting from the power of two `current_value`
    return min_value > current_value/2 ? current_value : nearest_power_of_two(min_value, current_value/2);
}


template <typename T, int MatrixSize, int MaxVecSize>
class BaseMatrix;

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

template <typename T, int MatrixSize, int MaxVecSize>
std::ostream & operator<<(std::ostream &os, BaseMatrix<T, MatrixSize, MaxVecSize> &mat) {
// Matrix printing function
    for (int i=0; i<MatrixSize; i++) {
        for (int j=0; j<MatrixSize; j++) {
            os << mat.array[i*BaseMatrix<T, MatrixSize, MaxVecSize>::VecSize + j] << ", ";
        }
        os << std::endl;
    }
    return os;
}

template <typename M>
static inline void matrix_mul_m_m(M &a, M &b, M &c) {
/*
 * Computes the following matrix product C = A*B
 * where A, B and C are BaseMatrix objects.
 * The idea is that we can perform the costly reduction for all the elements in a row
 * of C in one vector.
 * This use only vector operations so the compiler can optimize easily.
 */
    using pack_t = bs::pack<typename M::ElementType, M::VecSize>;
    /* Algorithm:
     * For each row of C matrix:
     *  * Load one element of A and broadcast it into vector.
     *  * Load the corresponding row of B into vector.
     *  * Computes element-wise product between these two vector.
     *  * Repeat for each element of A in the row and sum these results.
     *  * Store the sommation as corresponding row of C.
     */
    for (int i=0; i<M::MatSize; i++) {
        pack_t res = bs::Zero<pack_t>();
        int mult = M::VecSize*i;
        for (int j=0; j<M::MatSize; j++) {
            pack_t factor {a.array[mult + j]};
            pack_t row(&b.array[M::VecSize*j]);
            res += factor * row;
        }
        bs::aligned_store(res, &c.array[mult]);
    }
}

template <typename M>
static inline void matrix_mul_tm_m(M &a, M &b, M &c) {
/*
 * Computes the following matrix product C = t(A)*B
 * where A, B and C are BaseMatrix objects.
 * This code is nearly identical to matrix_mul_m_m but we
 * run through A in column instead of row
 */
    using pack_t = bs::pack<typename M::ElementType, M::VecSize>;
    for (int i=0; i<M::MatSize; i++) {
        pack_t res = bs::Zero<pack_t>();
        int mult = M::VecSize*i;
        for (int j=0; j<M::MatSize; j++) {
            pack_t factor {a.array[M::VecSize*j + i]};
            pack_t row(&b.array[M::VecSize*j]);
            res += factor * row;
        }
        bs::aligned_store(res, &c.array[mult]);
    }
}

template <typename M>
static inline void matrix_mul_m_mt(M &a, M &b, M &c) {
/*
 * Computes the following matrix product C = A*t(B)
 * where A, B and C are BaseMatrix objects.
 * This is slower than A*B product due to mandatory reduction.
 * The idea is that we don't need to transpose B beforehand. Since we have
 * to load columns of t(B) into vector register we can load row of B instead.
 * Assuming that B is store in row order, row of B are correctly aligned for loading.
 */
    using pack_t = bs::pack<typename M::ElementType, M::VecSize>;
    /* Algorithm:
     * For each C matrix element:
     *  * Load corresponding row of A into vector.
     *  * Load corresponding column of t(B) => Load corresponding row of B into vector.
     *  * Computes dot product between the two vector.
     *  * Store the resulting scalar of C.
     */
    for (int i=0; i<M::MatSize; i++) {
        pack_t row(&a.array[M::VecSize*i]);
        for (int j=0; j<M::MatSize; j++) {
            pack_t row_transpose(&b.array[M::VecSize*j]);
            // Dot is a slow operation but it will get better with newer hardware.
            c.array[M::VecSize*i + j] = bs::dot(row, row_transpose);
        }
    }
}


template <typename T, int MatrixSize, int MaxVecSize>
class BaseMatrix {
/* Class for matrix object
 * Matrix object are linearized 2D array with padded line to fit vector size
 */
    static_assert(MatrixSize <= MaxVecSize, "Matrix size must be less than maximum vector size");
    static_assert((MaxVecSize >= 4) & !(MaxVecSize & (MaxVecSize - 1)), "Maximum vector size must be a power of two.");

    using matrix_t = BaseMatrix<T, MatrixSize, MaxVecSize>;
    using ElementType = T;
    static constexpr int MatSize = MatrixSize;
    // We use the smallest vector size possible
    static constexpr int VecSize = nearest_power_of_two(MatrixSize, MaxVecSize);
    public:
    BaseMatrix() = default;
    BaseMatrix(float const a[]) {
        if (MatSize == VecSize) { // In this case there is no padding, we can copy directly the array
            std::memcpy(this->array, a, sizeof(T)*MatSize*VecSize);
        }
        else {
            for (int i=0; i<MatSize; i++) {
                std::memcpy(&this->array[i*VecSize], &a[i*MatSize], sizeof(T)*MatSize);
            }
        }
    }

    matrix_t operator=(float const a[]) {
        if (MatSize == VecSize) {
            std::memcpy(this->array, a, sizeof(T)*MatSize*VecSize);
        }
        else {
            for (int i=0; i<MatSize; i++) {
                std::memcpy(&this->array[i*VecSize], &a[i*MatSize], sizeof(T)*MatSize);
            }
        }
        return *this;
    }
    matrix_t operator=(matrix_t &other) {
        std::memcpy(this->array, other.array, sizeof(T)*MatSize*VecSize);
        return *this;
    }


    friend void matrix_mul_m_m<matrix_t>(matrix_t &a, matrix_t &b, matrix_t &c);
    friend void matrix_mul_tm_m<matrix_t>(matrix_t &a, matrix_t &b, matrix_t &c);
    friend void matrix_mul_m_mt<matrix_t>(matrix_t &a, matrix_t &b, matrix_t &c);
    friend std::ostream & operator<<<T, MatrixSize, MaxVecSize>(std::ostream &os, matrix_t &mat);

    protected:
    alignas(sizeof(T)*VecSize) float array[MatSize*VecSize] = {0};

};
