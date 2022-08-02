#ifndef INVERSION_CUSTOM_H
#define INVERSION_CUSTOM_H

#include "benchmark/benchmark.h"
#include "fast5x5/fast5x5.hpp"
#include "benchmarks/shared/common.hpp"
#include "benchmarks/shared/random.hpp"

template<int SIZE = 8, typename T = float>
static void inversion_custom(benchmark::State& state) {
    alignas(32) T a[SIZE * SIZE];

    for (int i = 0; i < SIZE; i++) {
        for (int j = i; j < SIZE; j++) {
            // filling the upper triangle
            a[i * SIZE + j] = randomEntry<T>(-1.0, 1.0);
			// copying the upper triangle element into
			// the lower triangle
            a[j * SIZE + i] = a[i * SIZE + j];
        }
    }

    using M = BaseMatrix<T, SIZE, SIZE>;
    M m1(a), res;

    for (auto _ : state) {
        benchmark::DoNotOptimize(res);

        Inverse<T, SIZE>::inverse(m1, res);
    }
}

#endif  // INVERSION_CUSTOM_H
