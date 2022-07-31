#ifndef GEMM_CUSTOM_H
#define GEMM_CUSTOM_H

#include "benchmark/benchmark.h"
#include "fast5x5/fast5x5.hpp"
#include "benchmarks/shared/common.hpp"
#include "benchmarks/shared/random.hpp"

static void gemm_custom(benchmark::State& state) {
    alignas(32) float a[SIZE * SIZE];
    alignas(32) float b[SIZE * SIZE];

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            a[i * SIZE + j] = randomDouble(-1.0, 1.0);
            b[i * SIZE + j] = randomDouble(-1.0, 1.0);
        }
    }

    using M = BaseMatrix<float, SIZE, SIZE>;
    M m1(a), m2(b), res;

    for (auto _ : state) {
        benchmark::DoNotOptimize(res);

        matrix_mul_m_m(m1, m2, res);
    }
}

#endif  // GEMM_CUSTOM_H
