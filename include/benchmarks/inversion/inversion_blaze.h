#ifndef INVERSION_BLAZE_H
#define INVERSION_BLAZE_H

#include "benchmark/benchmark.h"
#include "blaze/Math.h"
#include "benchmarks/shared/common.hpp"
#include "benchmarks/shared/random.hpp"

template<unsigned long SIZE = 8UL, typename T = float>
static void inversion_blaze(benchmark::State& state) {
    blaze::StaticMatrix<T, SIZE, SIZE, blaze::rowMajor> m;

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE - i; j++) {
            m(i, j) = randomEntry<T>(-1.0, 1.0);
            m(j, i) = m(i, j);
        }
    }

	blaze::SymmetricMatrix<blaze::StaticMatrix<T, SIZE, SIZE, blaze::rowMajor>> m1(m), res;

    for (auto _ : state) {
        benchmark::DoNotOptimize(res);

        res = blaze::inv(m1);
    }
}

#endif  // INVERSION_BLAZE_H
