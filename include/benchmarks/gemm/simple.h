#ifndef GEMM_SIMPLE_H
#define GEMM_SIMPLE_H

#include "benchmark/benchmark.h"
#include "benchmarks/shared/common.hpp"
#include "gemm_header.h" // for the gemm<> function

template<int SIZE = 8, typename T = float>
static void gemm_simple(benchmark::State& state) {
    alignas(32) T a[SIZE * SIZE];
    alignas(32) T b[SIZE * SIZE];
    alignas(32) T c[SIZE * SIZE];

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            a[i * SIZE + j] = i + j;
        }
    }

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            T val;
            if (i == 0 && j == 1)
                val = -1;
            else if (i == 1 && j == 0)
                val = 1;
            else if (i > 1 && i == j && i % 2)
                val = -1;
            else if (i > 1 && i == j && !(i % 2))
                val = 1;
            else
                val = 0;
            b[i * SIZE + j] = val;
        }
    }

    for (auto _ : state) {
        benchmark::DoNotOptimize(c);

        gemm<T, SIZE>(a, b, c);
        gemm<T, SIZE>(b, c, a);

        // print_matrix<float>(a, SIZE, SIZE);
    }
}

#endif  // GEMM_SIMPLE_H
