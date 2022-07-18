#ifndef FAST5x5_HPP
#define FAST5x5_HPP

#include <array>
#include <ostream>
#include <utility>
#include <xsimd/xsimd.hpp>

namespace xs = xsimd;

constexpr int nearest_power_of_two(int min_value, int current_value) {
    // Computes the nearest power of two relative to `min_value` starting from
    // the power of two `current_value`
    return min_value <= current_value
               ? current_value
               : nearest_power_of_two(min_value, current_value * 2);
}

template <typename T, int NRows, int NCols>
class BaseMatrix;

template <typename T, int NCols>
class Vector;

template <typename M>
static inline void matrix_add(M &a, M &b, M &c) {
    using batch_t = typename M::batch_t;
    for (int i = 0; i < M::NRows; i++) {
        int index = M::VecSize * i;
        batch_t row_a(&a.array[index], xs::aligned_mode());
        batch_t row_b(&b.array[index], xs::aligned_mode());
        row_a += row_b;
        row_a.store_aligned(&c.array[index]);
    }
}

template <typename M>
static inline void matrix_sub(M &a, M &b, M &c) {
    using batch_t = typename M::batch_t;
    for (int i = 0; i < M::NRows; i++) {
        int index = M::VecSize * i;
        batch_t row_a(&a.array[index], xs::aligned_mode());
        batch_t row_b(&b.array[index], xs::aligned_mode());
        row_a -= row_b;
        row_a.store_aligned(&c.array[index]);
    }
}

template <typename T, int l, int m, int n>
static inline void matrix_mul_m_m(BaseMatrix<T, l, m> &a,
                                  BaseMatrix<T, m, n> &b,
                                  BaseMatrix<T, l, n> &c) {
    /*
     * Computes the following matrix product C = A*B
     * where A, B and C are BaseMatrix objects.
     * The idea is that we can perform the costly reduction for all the elements
     * in a row of C in one vector. This use only vector operations so the
     * compiler can optimize easily.
     */
    static constexpr int LeftVecSize = BaseMatrix<T, l, m>::VecSize;
    static constexpr int RightVecSize = BaseMatrix<T, m, n>::VecSize;
    using batch_t = xs::batch<T, RightVecSize>;
    /* Algorithm:
     * For each row of C matrix:
     *  * Load one element of A and broadcast it into vector.
     *  * Load the corresponding row of B into vector.
     *  * Computes element-wise product between these two vector.
     *  * Repeat for each element of A in the row and sum these results.
     *  * Store the summation as corresponding row of C.
     */
    for (int i = 0; i < l; i++) {
        batch_t res = xs::zero<batch_t>();
        for (int j = 0; j < m; j++) {
            batch_t factor(a.array[LeftVecSize * i + j]);
            batch_t row(&b.array[RightVecSize * j], xs::aligned_mode());
            res += factor * row;
        }
        res.store_aligned(&c.array[RightVecSize * i]);
    }
}

template <typename T, int l, int m, int n>
static inline void matrix_mul_mt_m(BaseMatrix<T, m, l> &a,
                                   BaseMatrix<T, m, n> &b,
                                   BaseMatrix<T, l, n> &c) {
    /*
     * Computes the following matrix product C = t(A)*B
     * where A, B and C are BaseMatrix objects.
     * This code is nearly identical to matrix_mul_m_m but we
     * run through A in column instead of row
     */
    static constexpr int LeftVecSize = BaseMatrix<T, m, l>::VecSize;
    static constexpr int RightVecSize = BaseMatrix<T, m, n>::VecSize;
    using batch_t = xs::batch<T, RightVecSize>;
    for (int i = 0; i < l; i++) {
        batch_t res = xs::zero<batch_t>();
        for (int j = 0; j < m; j++) {
            batch_t factor(a.array[LeftVecSize * j + i]);
            batch_t row(&b.array[RightVecSize * j], xs::aligned_mode());
            res += factor * row;
        }
        res.store_aligned(&c.array[RightVecSize * i]);
    }
}

template <typename T, int l, int m, int n>
static inline void matrix_mul_m_mt(BaseMatrix<T, l, m> &a,
                                   BaseMatrix<T, n, m> &b,
                                   BaseMatrix<T, l, n> &c) {
    /*
     * Computes the following matrix product C = A*t(B)
     * where A, B and C are BaseMatrix objects.
     * This is slower than A*B product due to mandatory reduction.
     * The idea is that we don't need to transpose B beforehand. Since we have
     * to load columns of t(B) into vector register we can load row of B
     * instead. Assuming that B is store in row order, row of B are correctly
     * aligned for loading.
     */
    static constexpr int VecSize =
        BaseMatrix<T, l, m>::VecSize;  // VecSize are the same for left and
                                       // right matrices
    static constexpr int ResVecSize = BaseMatrix<T, l, n>::VecSize;
    using batch_t = xs::batch<T, VecSize>;
    /* Algorithm:
     * For each C matrix element:
     *  * Load corresponding row of A into vector.
     *  * Load corresponding column of t(B) => Load corresponding row of B into
     * vector.
     *  * Computes dot product between the two vector.
     *  * Store the resulting scalar of C.
     */
    for (int i = 0; i < l; i++) {
        batch_t row(&a.array[VecSize * i]);
        for (int j = 0; j < n; j++) {
            batch_t row_transpose(&b.array[VecSize * j], xs::aligned_mode());
            // Dot is a slow operation but it will get better with newer
            // hardware.
            c.array[ResVecSize * i + j] = xs::hadd(row * row_transpose);
        }
    }
}

template <typename T, int l, int m>
static inline void matrix_mul_m_v(BaseMatrix<T, l, m> &a, Vector<T, m> &b,
                                  Vector<T, l> &c) {
    static constexpr int VecSize = BaseMatrix<T, l, m>::VecSize;

    using batch_t = xs::batch<T, VecSize>;
    batch_t vector(&b.array[0], xs::aligned_mode());

    for (int i = 0; i < l; i++) {
        batch_t row(&a.array[VecSize * i], xs::aligned_mode());
        c.array[i] = xs::hadd(row * vector);
    }
}

template <typename T, int Size>
class Inverse {
    using M = BaseMatrix<T, Size, Size>;

   public:
    static void inverse(M &a, M &inv) {
        /* Computes inverse of `a` by using Cholesky decomposition.
         * M must be symmetric, positive-definite.
         * a = t(r)*r, where r is upper triangular.
         * a^-1 = (r^-1)*t(r^-1) = inv
         */
        M r;
        using batch_t = typename M::batch_t;

        // Cholesky decomposition
        for (int i = 0; i < M::NRows; i++) {
            batch_t sum_row = xs::zero<batch_t>();

            for (int j = 0; j < i; j++) {
                batch_t cur_row(&r.array[j * M::VecSize], xs::aligned_mode());
                batch_t factor(r.array[j * M::VecSize + i]);
                sum_row += cur_row * factor;
            }

            batch_t res_row(&a.array[i * M::VecSize], xs::aligned_mode());
            res_row -= sum_row;
            batch_t diviser(1 / std::sqrt(res_row[i]));
            res_row *= diviser;
            res_row.store_aligned(&r.array[i * M::VecSize]);
        }

        M inv_r;
        static M Id(1);
        // Inversion of R by backward substitution
        for (int i = (M::NRows - 1); i >= 0; i--) {
            batch_t sum_row = xs::zero<batch_t>();

            for (int j = (M::NRows - 1); j > i; j--) {
                batch_t cur_row(&inv_r.array[j * M::VecSize],
                                xs::aligned_mode());
                batch_t factor(r.array[i * M::VecSize + j]);
                sum_row += cur_row * factor;
            }

            batch_t res_row(&Id.array[i * M::VecSize], xs::aligned_mode());
            res_row -= sum_row;
            batch_t diviser(1 / r.array[i * M::VecSize + i]);
            res_row *= diviser;
            res_row.store_aligned(&inv_r.array[i * M::VecSize]);
        }

        // Compute inverse of initial matrix
        /* TODO: Since inv_r is a triangular matrix there is room
         * for optimisation on this product
         */
        matrix_mul_m_mt(inv_r, inv_r, inv);
    }
};

template <typename T>
class Inverse<T, 2> {
    using M = BaseMatrix<T, 2, 2>;

   public:
    static void inverse(M &a, M &inv) {
        T inv_det = 1 / (a.array[0] * a.array[M::VecSize + 1] -
                         a.array[1] * a.array[1]);
        inv.array[0] = inv_det * a.array[M::VecSize + 1];
        inv.array[1] = inv.array[M::VecSize] = -inv_det * a.array[1];
        inv.array[M::VecSize + 1] = inv_det * a.array[0];
    }
};

template <typename T, int NumberRows, int NumberCols>
class BaseMatrix {
    /* Class for matrix object
     * Matrix object are linearized 2D array with padded line to fit vector size
     */
   protected:
    // We use the smallest vector size possible
    static constexpr int VecSize = nearest_power_of_two(NumberCols, 1);

    static xs::batch_bool<T, VecSize> select_mask() {
        return select_mask_impl(std::make_index_sequence<VecSize>());
    }

    template <std::size_t... Indices>
    static xs::batch_bool<T, VecSize> select_mask_impl(
        std::index_sequence<Indices...>) {
        return xs::batch_bool<T, VecSize>((Indices < NumberCols)...);
    }

    using matrix_t = BaseMatrix<T, NumberRows, NumberCols>;
    using batch_t = xs::batch<T, VecSize>;

   public:
    using ElementType = T;
    static constexpr int NRows = NumberRows;
    static constexpr int NCols = NumberCols;

    BaseMatrix() = default;
    BaseMatrix(T const a[]) {
        for (int i = 0; i < NRows; i++) {
            // In this case we copy data row by row
            batch_t row(&a[i * NCols], xs::unaligned_mode());
            if (NCols != VecSize)
                row = xs::select(select_mask(), row, xs::zero<batch_t>());
            row.store_aligned(&this->array[i * VecSize]);
        }
    }

    BaseMatrix(T const a) {
        for (int i = 0; i < NRows; i++) {
            array[VecSize * i + i] = a;
        }
    }

    matrix_t operator=(T const a[]) {
        for (int i = 0; i < NRows; i++) {
            // In this case we copy data row by row
            batch_t row(&a[i * NCols], xs::unaligned_mode());
            if (NCols != VecSize)
                row = xs::select(select_mask(), row, xs::zero<batch_t>());
            row.store_aligned(&this->array[i * VecSize]);
        }
        return *this;
    }

    matrix_t operator=(matrix_t &other) {
        std::memcpy(this->array, other.array, sizeof(T) * NRows * VecSize);
        return *this;
    }

    std::array<ElementType, NRows * NCols> dump_array() const {
        std::array<ElementType, NRows * NCols> returned_array;
        if (NCols == VecSize) {  // In this case there is no padding, we can
                                 // copy directly the array
            std::memcpy(&returned_array[0], this->array,
                        sizeof(T) * NRows * VecSize);
        } else {
            for (int i = 0; i < NRows; i++) {
                // std::memcpy(&returned_array[i*NCols],
                // &this->array[i*VecSize], sizeof(T)*NCols);
                for (int j = 0; j < NCols; j++) {
                    returned_array[i * NCols + j] =
                        this->array[i * VecSize + j];
                }
            }
        }
        return returned_array;
    }

    void store(T addr[]) const {
        if (NCols != VecSize) {
            for (int i = 0; i < NRows - 1; i++) {
                batch_t row(&this->array[i * VecSize], xs::aligned_mode());
                row.store_unaligned(&addr[i * NCols]);
            }
            std::memcpy(&addr[(NRows - 1) * NCols],
                        &this->array[(NRows - 1) * VecSize], sizeof(T) * NCols);
        } else {
            for (int i = 0; i < NRows; i++) {
                batch_t row(&this->array[i * VecSize], xs::aligned_mode());
                row.store_unaligned(&addr[i * NCols]);
            }
        }
    }

    bool is_padding_zero() const {
        bool padding_ok = true;
        for (int i = 0; i < NRows; i++) {
            for (int j = NCols; j < VecSize; j++) {
                if (array[i * VecSize + j] != 0)
                    padding_ok = false;
            }
        }
        return padding_ok;
    }

   private:
    friend void matrix_add<matrix_t>(matrix_t &a, matrix_t &b, matrix_t &c);
    friend void matrix_sub<matrix_t>(matrix_t &a, matrix_t &b, matrix_t &c);

    template <typename U, int l, int m, int n>
    friend void matrix_mul_m_m(BaseMatrix<U, l, m> &a, BaseMatrix<U, m, n> &b,
                               BaseMatrix<U, l, n> &c);

    template <typename U, int l, int m, int n>
    friend void matrix_mul_mt_m(BaseMatrix<U, m, l> &a, BaseMatrix<U, m, n> &b,
                                BaseMatrix<U, l, n> &c);

    template <typename U, int l, int m, int n>
    friend void matrix_mul_m_mt(BaseMatrix<U, l, m> &a, BaseMatrix<U, n, m> &b,
                                BaseMatrix<U, l, n> &c);

    template <typename U, int l, int m>
    friend void matrix_mul_m_v(BaseMatrix<U, l, m> &a, Vector<U, m> &b,
                               Vector<U, l> &c);

    friend class Inverse<T, NCols>;

    friend std::ostream &operator<<(std::ostream &os, const matrix_t &mat) {
        // Matrix printing function
        for (int i = 0; i < NRows; i++) {
            for (int j = 0; j < NCols; j++) {
                os << mat.array[i * BaseMatrix<T, NRows, NCols>::VecSize + j]
                   << ", ";
            }
            os << std::endl;
        }
        return os;
    }

   protected:
    alignas(sizeof(T) * VecSize) T array[NRows * VecSize] = {0};
};

template <typename T, int NumberCols>
class Vector : public BaseMatrix<T, 1, NumberCols> {
   public:
    using BaseMatrix<T, 1, NumberCols>::BaseMatrix;
    using BaseMatrix<T, 1, NumberCols>::operator=;

   protected:
    using vector_t = Vector<T, NumberCols>;

   private:
    template <typename U, int l, int m>
    friend void matrix_mul_m_v(BaseMatrix<U, l, m> &a, Vector<U, m> &b,
                               Vector<U, l> &c);

    friend void matrix_add<vector_t>(vector_t &a, vector_t &b, vector_t &c);

    friend void matrix_sub<vector_t>(vector_t &a, vector_t &b, vector_t &c);
};

#endif // FAST5x5_HPP
