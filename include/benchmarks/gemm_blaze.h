#ifndef GEMM_BLAZE_H
#define GEMM_BLAZE_H

#include "benchmark/benchmark.h"
#include "blaze/Math.h"
#include "gemm_header.h"
#include "random.hpp"

static void gemm_blaze(benchmark::State& state) {
    blaze::StaticMatrix<float, SIZE, SIZE, blaze::rowMajor> m1, m2, res;

    m1 =
        blaze::generate(SIZE, SIZE, []() { return RandomFloat(0, 100'000.0); });
    m2 =
        blaze::generate(SIZE, SIZE, []() { return RandomFloat(0, 100'000.0); });

    for (auto _ : state) {
        benchmark::DoNotOptimize(res);

        res = m1 * m2;
    }
}

#endif  // GEMM_BLAZE_H
