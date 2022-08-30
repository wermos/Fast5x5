#ifndef INVERSION_BLAZE_H
#define INVERSION_BLAZE_H

#include "benchmark/benchmark.h"
#include "blaze/Math.h"
#include "benchmarks/shared/common.hpp"

static void inversion_blaze(benchmark::State& state) {
	using M = blaze::SymmetricMatrix<blaze::StaticMatrix<float, SIZE, SIZE, blaze::rowMajor>>;

	M m(genRandomBlazeSymMat<float, SIZE, SIZE>());
	M res;

    for (auto _ : state) {
		benchmark::DoNotOptimize(m);

        res = blaze::inv(m);

        benchmark::DoNotOptimize(res);
    }
}

#endif // INVERSION_BLAZE_H
