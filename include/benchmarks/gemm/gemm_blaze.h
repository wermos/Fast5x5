#ifndef GEMM_BLAZE_H
#define GEMM_BLAZE_H

#include "benchmark/benchmark.h"
#include "blaze/Math.h"
#include "shared/common.hpp"
#include "random.hpp"

static void gemm_blaze(benchmark::State& state) {
    blaze::StaticMatrix<float, SIZE, SIZE, blaze::rowMajor> m1, m2, res;

    m1 =
        blaze::generate(SIZE, SIZE, [](std::size_t i, std::size_t j) { return randomFloat(-1.0, 1.0); });
    m2 =
        blaze::generate(SIZE, SIZE, [](std::size_t i, std::size_t j) { return randomFloat(-1.0, 1.0); });

    for (auto _ : state) {
        benchmark::DoNotOptimize(res);

        res = m1 * m2;
    }
}

#endif  // GEMM_BLAZE_H
