#ifndef GEMM_HEADER_H
#define GEMM_HEADER_H

#include <iostream>

template <typename T>
void print_matrix(T *matrix, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            std::cout << matrix[i * m + j] << (j == m - 1 ? "" : ", ");
        }
        std::cout << std::endl;
    }
}

template <typename T, int N>
void gemm(T *a, T *b, T *c) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            T res = 0;
            for (int k = 0; k < N; k++)
                res += a[i * N + k] * b[k * N + j];
            c[i * N + j] = res;
        }
    }
}

#endif  // GEMM_HEADER_H
