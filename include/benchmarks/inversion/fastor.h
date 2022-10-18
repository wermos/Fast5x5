#ifndef INVERSION_FASTOR_H
#define INVERSION_FASTOR_H

#include "benchmark/benchmark.h"
#include "Fastor/Fastor.h"
#include "benchmarks/shared/common.hpp"

static void inversion_fastor(benchmark::State& state) {
	Fastor::Tensor<float, SIZE, SIZE> m = genRandomFastorSymMat<float, SIZE, SIZE>();
	Fastor::Tensor<float, SIZE, SIZE> res;

    for (auto _ : state) {
		benchmark::DoNotOptimize(m);

		res = inverse(m);

        benchmark::DoNotOptimize(res);
    }
}

#endif // INVERSION_FASTOR_H
