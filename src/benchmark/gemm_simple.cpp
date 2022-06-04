#include <iostream>

#include "gemm_header.h"

template <typename T>
void print_matrix(T* matrix, int n, int m) {
    for (int i=0; i<n; i++) {
        for (int j=0; j<m; j++) {
            std::cout << matrix[i*m+j] << (j == m-1 ? "" : ", ");
        }
        std::cout << std::endl;
    }
}

template <typename T, int N>
void gemm(T *a, T *b, T*c) {
    for (int i=0; i < N; i++) {
        for (int j=0; j < N; j++) {
            T res = 0;
            for (int k=0; k < N; k++) res += a[i*N+k] * b[k*N+j];
            c[i*N+j] = res;
        }
    }
}

int main(int argc, char **argv) {
    alignas(32) float a[SIZE*SIZE];
    alignas(32) float b[SIZE*SIZE];
    alignas(32) float c[SIZE*SIZE];

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

    for (unsigned int i=0; i<REPEAT; i++) { // Computation Loop
        gemm<float, SIZE>(a, b, c);
        gemm<float, SIZE>(b, c, a);
    }

    print_matrix<float>(a, SIZE, SIZE);
    return 0;
}
