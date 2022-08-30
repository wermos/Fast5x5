#ifndef FREE_TO_BOUND_FASTOR_H 
#define FREE_TO_BOUND_FASTOR_H

#include "benchmark/benchmark.h"
#include "fast5x5/fast5x5.hpp"
#include "benchmarks/shared/common.hpp"

static void freeToBound_fastor(benchmark::State& state) {
    Fastor::Tensor<float, 6, 6> m1 = genRandomFastorMat<float, 6, 6>();
    Fastor::Tensor<float, 6, 8> m2 = genRandomFastorMat<float, 6, 8>();
    Fastor::Tensor<float, 6, 8> res;

    for (auto _ : state) {
		benchmark::DoNotOptimize(m1);
		benchmark::DoNotOptimize(m2);

		res = Fastor::matmul(m1, m2);

        benchmark::DoNotOptimize(res);
    }
}

#endif // FREE_TO_BOUND_FASTOR_H
