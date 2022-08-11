#ifndef FREE_TO_BOUND_EIGEN_H
#define FREE_TO_BOUND_EIGEN_H

#include "Eigen/Dense"
#include "benchmark/benchmark.h"
#include "benchmarks/shared/common.hpp"

static void freeToBound_eigen(benchmark::State& state) {
    Eigen::Matrix<float, 6, 6> m1;
    Eigen::Matrix<float, 6, 8> m2, res;

    m1 = Eigen::Matrix<float, 6, 6>::Random();
    m2 = Eigen::Matrix<float, 6, 8>::Random();

    for (auto _ : state) {
        benchmark::DoNotOptimize(res);

        res = m1 * m2;
    }
}

#endif // FREE_TO_BOUND_EIGEN_H
