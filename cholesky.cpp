#include<iostream>
#include<cstring>

#include "../dsl/fast_matrix.hpp"

#ifndef SIZE
#define SIZE 4
#endif

#ifndef VECSIZE
#define VECSIZE 8
#endif

template <typename M>
void chol_inv(M &a, M &i);

template<typename T, int MatrixSize, int MaxVecSize>
class InvertibleMatrix : public BaseMatrix<T, MatrixSize, MaxVecSize> {
    protected:
    using matrix_t = InvertibleMatrix<T, MatrixSize, MaxVecSize>;
    using ElementType = T;
    using pack_t = typename BaseMatrix<T, MatrixSize, MaxVecSize>::pack_t;
    static constexpr int MatSize = MatrixSize;
    static constexpr int VecSize = BaseMatrix<T, MatrixSize, MaxVecSize>::VecSize;

    public:
    InvertibleMatrix() = default;

    InvertibleMatrix(T const a[])
    : BaseMatrix<T, MatrixSize, MaxVecSize>(a)
    {}

    InvertibleMatrix(T const a)
    : BaseMatrix<T, MatrixSize, MaxVecSize>(a)
    {}
    private:
    friend void chol_inv<matrix_t>(matrix_t &a, matrix_t &i);
    friend void matrix_mul_m_m<matrix_t>(matrix_t &a, matrix_t &b, matrix_t &c);
    friend void matrix_mul_mt_m<matrix_t>(matrix_t &a, matrix_t &b, matrix_t &c);
    friend void matrix_mul_m_mt<matrix_t>(matrix_t &a, matrix_t &b, matrix_t &c);
};

template <typename M>
void chol_inv(M &a, M &inv) {
    M r;
    using pack_t = typename M::pack_t;

    // Cholesky decomposition
    for (int i=0; i<M::MatSize; i++) {
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

    M tmp;
    static M Id(1);
    // Inversion of R by backward substitution
    for (int i=(M::MatSize-1); i>=0; i--) {
        pack_t sum_row = bs::Zero<pack_t>();

        for (int j=(M::MatSize-1); j > i; j--) {
            pack_t cur_row(&tmp.array[j*M::VecSize]);
            pack_t factor {r.array[i*M::VecSize+j]};
            sum_row += cur_row*factor;
        }

        pack_t res_row(&Id.array[i*M::VecSize]);
        res_row -= sum_row;
        pack_t diviser {1/r.array[i*M::VecSize+i]};
        res_row *= diviser;
        bs::aligned_store(res_row, &tmp.array[i*M::VecSize]);
    }


    // Compute inverse of initial matrix
    matrix_mul_mt_m(tmp, tmp, inv);

}

int main(int argc, char *argv[]) {
    alignas(32) float a[SIZE*SIZE] {0};
    alignas(32) float b[SIZE*SIZE];
    alignas(32) float p[SIZE*SIZE];

    for (int i=0; i<SIZE; i++) {
        for (int j=0; j<SIZE; j++) {
            if(j>=i)  a[i*SIZE+j] = j-i+1;

        }
    }

    for (int i=0; i<SIZE; i++) {
        for (int j=0; j<SIZE; j++) {
            float val;
            if (i == 0 && j == 1) val = 1;
            else if (i == 1 && j == 0) val = 1;
            else if (i > 1 && i == j && i % 2) val = 1;
            else if (i > 1 && i == j && !(i % 2)) val = 1;
            else val = 0;
            b[i*SIZE+j] = val;
        }
    }
    if (SIZE % 2 == 0) {
        b[SIZE*SIZE-1] = 1;
    }

    using M = InvertibleMatrix<float, SIZE, VECSIZE>;
    M A(a), P(b), I, Tmp;

//    std::cout << pa << std::endl;
//    std::cout << pb << std::endl;

    std::cout << P << std::endl;
    matrix_mul_mt_m(A, A, Tmp); //Symetric positive definite matrix
    A = Tmp;
    std::cout << A << std::endl;

//    for (unsigned int i=0; i<20000000; i++) {
    for (unsigned int k = 0; k< 1000000; k++) {
        A = Tmp;
        matrix_mul_m_m(P, A, Tmp);
        matrix_mul_mt_m(Tmp, P, A);
        Tmp = A;
        for (unsigned int i=0; i<20; i++) {
            chol_inv(A, I);
            chol_inv(I, A);
        }
    }

    std::cout << A << std::endl;
    return 0;
}
