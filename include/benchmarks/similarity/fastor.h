#ifndef SIMILARITY_FASTOR_H 
#define SIMILARITY_FASTOR_H

#include "benchmark/benchmark.h"
#include "Fastor/Fastor.h"
#include "benchmarks/shared/common.hpp"

static void similarity_fastor(benchmark::State& state) {
	Fastor::Tensor<float, SIZE, SIZE> m1 = genRandomFastorMat<float, SIZE, SIZE>();
	Fastor::Tensor<float, SIZE, SIZE> m2 = genRandomFastorMat<float, SIZE, SIZE>();
	Fastor::Tensor<float, SIZE, SIZE> res, temp;

    for (auto _ : state) {
		benchmark::DoNotOptimize(m1);
		benchmark::DoNotOptimize(m2);

		res = Fastor::matmul(Fastor::matmul(m1, m2), Fastor::transpose(m1));

        benchmark::DoNotOptimize(res);
    }
}

#endif // SIMILARITY_FASTOR_H
