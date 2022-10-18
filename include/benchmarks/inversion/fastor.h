#pragma once

#include "benchmark/benchmark.h"
#include "Fastor/Fastor.h"
#include "benchmarks/shared/common.hpp"

template <unsigned long SIZE = 8UL, T = float>
static void inversion_fastor(benchmark::State& state) {
	Fastor::Tensor<T, SIZE, SIZE> m = genRandomFastorSymMat<T, SIZE, SIZE>();
	Fastor::Tensor<T, SIZE, SIZE> res;

    for (auto _ : state) {
		benchmark::DoNotOptimize(m);

		res = inverse(m);

        benchmark::DoNotOptimize(res);
    }
}

