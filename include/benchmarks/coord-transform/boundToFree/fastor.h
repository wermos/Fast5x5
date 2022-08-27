#ifndef BOUND_TO_FREE_FASTOR_H 
#define BOUND_TO_FREE_FASTOR_H

#include "benchmark/benchmark.h"
#include "Fastor/Fastor.h"
#include "benchmarks/shared/common.hpp"

static void boundToFree_fastor(benchmark::State& state) {
	Fastor::Tensor<float, 6, 8> m1 = genRandomFastorMat<float, 6, 8>();
	Fastor::Tensor<float, 8, 8> m2 = genRandomFastorMat<float, 8, 8>();
	Fastor::Tensor<float, 6, 8> res;

    for (auto _ : state) {
        benchmark::DoNotOptimize(res);

		res = Fastor::matmul(m1, m2);
    }
}

#endif // BOUND_TO_FREE_FASTOR_H
