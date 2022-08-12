#ifndef BOUND_TO_FREE_EIGEN_H
#define BOUND_TO_FREE_EIGEN_H

#include "Eigen/Dense"
#include "benchmark/benchmark.h"
#include "benchmarks/shared/common.hpp"

template <typename T = float>
static void boundToFree_eigen(benchmark::State& state) {
    Eigen::Matrix<T, 6, 8> m1, res;
    Eigen::Matrix<T, 8, 8> m2;

    m1 = Eigen::Matrix<T, 6, 8>::Random();
    m2 = Eigen::Matrix<T, 8, 8>::Random();

    for (auto _ : state) {
        benchmark::DoNotOptimize(res);

        res = m1 * m2;
    }
}

#endif  // BOUND_TO_FREE_EIGEN_H
