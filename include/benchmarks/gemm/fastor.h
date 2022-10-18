#pragma once

#include "benchmark/benchmark.h"
#include "Fastor/Fastor.h"
#include "benchmarks/shared/common.hpp"

template <unsigned long SIZE = 8UL, typename T = float>
static void gemm_fastor(benchmark::State& state) {
	Fastor::Tensor<T, SIZE, SIZE> m1 = genRandomFastorMat<T, SIZE, SIZE>();
	Fastor::Tensor<T, SIZE, SIZE> m2 = genRandomFastorMat<T, SIZE, SIZE>();
	Fastor::Tensor<T, SIZE, SIZE> res;

    for (auto _ : state) {
		benchmark::DoNotOptimize(m1);
		benchmark::DoNotOptimize(m2);

		res = Fastor::matmul(m1, m2);

        benchmark::DoNotOptimize(res);
    }
}

#endif  // FASTOR_CUSTOM_H
