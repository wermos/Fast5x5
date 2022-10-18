#pragma once

#include "benchmark/benchmark.h"
#include "Fastor/Fastor.h"
#include "benchmarks/shared/common.hpp"

template <typename T = float>
static void boundToFree_fastor(benchmark::State& state) {
	Fastor::Tensor<T, 6, 8> m1 = genRandomFastorMat<T, 6, 8>();
	Fastor::Tensor<T, 8, 8> m2 = genRandomFastorMat<T, 8, 8>();
	Fastor::Tensor<T, 6, 8> res;

    for (auto _ : state) {
		benchmark::DoNotOptimize(m1);
		benchmark::DoNotOptimize(m2);

		res = Fastor::matmul(m1, m2);

        benchmark::DoNotOptimize(res);
    }
}

