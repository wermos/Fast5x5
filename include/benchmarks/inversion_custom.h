#ifndef INVERSION_CUSTOM_H
#define INVERSION_CUSTOM_H

#include "benchmark/benchmark.h"
#include "fast5x5/fast5x5.hpp"
#include "gemm_header.h"
#include "random.hpp"

static void inversion_custom(benchmark::State& state) {
    alignas(32) float a[SIZE * SIZE];

    for (int i = 0; i < SIZE; i++) {
        for (int j = i; j < SIZE; j++) {
            // filling the upper triangle
            a[i * SIZE + j] = randomFloat(-1.0, 1.0);
			// copying the upper triangle element into
			// the lower triangle
            a[j * SIZE + i] = a[i * SIZE + j];
        }
    }

    using M = BaseMatrix<float, SIZE, SIZE>;
    M m1(a), res;

    for (auto _ : state) {
        benchmark::DoNotOptimize(res);

        Inverse<float, 8>::inverse(m1, res);
    }
}

#endif  // INVERSION_CUSTOM_H
