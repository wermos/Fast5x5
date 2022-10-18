#ifndef FASTOR_CUSTOM_H
#define FASTOR_CUSTOM_H

#include "benchmark/benchmark.h"
#include "Fastor/Fastor.h"
#include "benchmarks/shared/common.hpp"

static void gemm_fastor(benchmark::State& state) {
	Fastor::Tensor<float, SIZE, SIZE> m1 = genRandomFastorMat<float, SIZE, SIZE>();
	Fastor::Tensor<float, SIZE, SIZE> m2 = genRandomFastorMat<float, SIZE, SIZE>();
	Fastor::Tensor<float, SIZE, SIZE> res;

    for (auto _ : state) {
		benchmark::DoNotOptimize(m1);
		benchmark::DoNotOptimize(m2);

		res = Fastor::matmul(m1, m2);

        benchmark::DoNotOptimize(res);
    }
}

#endif  // FASTOR_CUSTOM_H
