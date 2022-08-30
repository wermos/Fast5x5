#ifndef INVERSION_EIGEN_H
#define INVERSION_EIGEN_H

#include "Eigen/Dense"
#include "benchmark/benchmark.h"
#include "benchmarks/shared/common.hpp"

static void inversion_eigen(benchmark::State& state) {
    Eigen::Matrix<float, SIZE, SIZE> m, res;

    m = Eigen::Matrix<float, SIZE, SIZE>::Random();

    for (auto _ : state) {
		benchmark::DoNotOptimize(m);

        res = m.inverse();

        benchmark::DoNotOptimize(res);
    }
}

#endif // INVERSION_EIGEN_H
