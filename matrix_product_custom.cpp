#include<iostream>

#include"fast_matrix.hpp"

#ifndef SIZE
#define SIZE 4
#endif

#ifndef VECSIZE
#define VECSIZE 8
#endif

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
    M pa(a), pb(b), pf;

//    std::cout << pa << std::endl;
//    std::cout << pb << std::endl;

    for (unsigned int i=0; i<200000000; i++) {
        matrix_mul<M>(pb, pa, pf);
        matrix_mul<M>(pf, pb, pa);
        //matrix_mul_sym<M>(pb, pa, pf);
        //matrix_mul<M>(pf, pb, pa);
    }

    std::cout << pa << std::endl;
    return 0;
}
