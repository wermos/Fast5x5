#pragma once

#include "benchmark/benchmark.h"
#include "blaze/Math.h"
#include "benchmarks/shared/common.hpp"

template<unsigned long SIZE = 8UL, typename T = float>
static void inversion_blaze(benchmark::State& state) {
	using M = blaze::SymmetricMatrix<blaze::StaticMatrix<T, SIZE, SIZE, blaze::rowMajor>>;

	M m(genRandomBlazeSymMat<T, SIZE, SIZE>());
	M res;

    for (auto _ : state) {
        benchmark::DoNotOptimize(res);

        res = blaze::inv(m);
    }
}