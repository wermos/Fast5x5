#include<boost/simd/pack.hpp>
#include<boost/simd/constant/zero.hpp>
#include<boost/simd/function/aligned_store.hpp>
#include<iostream>
#include<cstring>


#ifndef SIZE
#define SIZE 4
#endif

namespace bs = boost::simd;

template <typename T, int MatSize, int VecSize>
class PaddedMatrix;
template <typename T, int MatSize, int VecSize>
void matrix_mul(PaddedMatrix<T, MatSize, VecSize> &a,
                PaddedMatrix<T, MatSize, VecSize> &b,
                PaddedMatrix<T, MatSize, VecSize> &c);

template <typename T, int MatSize, int VecSize>
std::ostream & operator<<(std::ostream &os, PaddedMatrix<T, MatSize, VecSize> &mat) {
    for (int i=0; i<MatSize; i++) {
        for (int j=0; j<MatSize; j++) {
            os << mat.array[i*VecSize + j] << ", ";
        }
        os << std::endl;
    }
    return os;
}

template <typename T, int MatSize, int VecSize>
class PaddedMatrix {
    static_assert(MatSize <= VecSize, "Matrix size is greater than vector size");
    using matrix_t = PaddedMatrix<T, MatSize, VecSize>;

    public:
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
    matrix_t operator=(PaddedMatrix<T, MatSize, VecSize> &other) {
        std::memcpy(this->array, other.array, sizeof(T)*MatSize*VecSize);
        return *this;
    }


    friend void matrix_mul<T, MatSize, VecSize>(matrix_t &a, matrix_t &b, matrix_t &c);
    friend std::ostream & operator<<<T, MatSize, VecSize>(std::ostream &os, matrix_t &mat);
    private:
    alignas(sizeof(T)*VecSize) float array[MatSize*VecSize] = {0};

};

template <typename T, int MatSize, int VecSize>
static inline void matrix_mul(PaddedMatrix<T, MatSize, VecSize> &a,
                PaddedMatrix<T, MatSize, VecSize> &b,
                PaddedMatrix<T, MatSize, VecSize> &c)
{
    using pack_t = bs::pack<T, VecSize>;
    for (int i=0; i<MatSize; i++) {
        pack_t res = bs::Zero<pack_t>();
        int mult = VecSize*i;
        for (int j=0; j<MatSize; j++) {
            pack_t factor {a.array[mult + j]};
            pack_t row(&b.array[VecSize*j]);
            res += factor * row;
        }
        bs::aligned_store(res, &c.array[mult]);
    }
}

int main(int argc, char **argv) {
    alignas(32) float a[SIZE*SIZE];
    alignas(32) float b[SIZE*SIZE];

    for (int i=0; i<SIZE; i++) {
        for (int j=0; j<SIZE; j++) {
            a[i*SIZE+j] = i+j;
        }
    }

    for (int i=0; i<SIZE; i++) {
        for (int j=0; j<SIZE; j++) {
            float val;
            if (i == 0 && j == 1) val = -1;
            else if (i == 1 && j == 0) val = 1;
            else if (i > 1 && i == j && i % 2) val = -1;
            else if (i > 1 && i == j && !(i % 2)) val = 1;
            else val = 0;
            b[i*SIZE+j] = val;
        }
    }

    PaddedMatrix<float, SIZE, 8> pa, pb, pf;
    pa = a;
    pb = b;

//    std::cout << pa << std::endl;
//    std::cout << pb << std::endl;

    for (unsigned int i=0; i<200000000; i++) {
        matrix_mul<float, SIZE, 8>(pa, pb, pf);
        matrix_mul<float, SIZE, 8>(pf, pb, pa);
    }

    std::cout << pa << std::endl;
    return 0;
}
