#include<iostream>
#include "gemm_header.h"
#include "../fast_matrix.hpp"

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

    using M = BaseMatrix<float, SIZE, VECSIZE>;
    M pa(a), pb(b), pc;

    for (unsigned int i=0; i < REPEAT; i++) {
        matrix_mul_m_m<M>(pa, pb, pc);
        matrix_mul_m_m<M>(pb, pc, pa);
    }

    std::cout << pa << std::endl;
    return 0;
}
