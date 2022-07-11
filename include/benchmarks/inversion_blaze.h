#ifndef INVERSION_BLAZE_H
#define INVERSION_BLAZE_H

#include "benchmark/benchmark.h"
#include "blaze/Math.h"
#include "gemm_header.h"
#include "random.hpp"

static void inversion_blaze(benchmark::State& state) {
    blaze::SymmetricMatrix<float, SIZE, SIZE, blaze::rowMajor> m1, res;

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE - i; j++) {
            // filling the upper triangle
            m1[i][j] = randomFloat(0, 100'000.0);
            m1[j][i] = m1[i][j];
        }
    }

    for (auto _ : state) {
        benchmark::DoNotOptimize(res);

        res = inv(m1);
    }
}

#endif  // INVERSION_BLAZE_H
