#pragma once

#include "Eigen/Dense"
#include "benchmark/benchmark.h"
#include "benchmarks/shared/common.hpp"

template <typename T = float>
static void freeToBound_eigen(benchmark::State& state) {
    Eigen::Matrix<T, 6, 6> m1;
    Eigen::Matrix<T, 6, 8> m2, res;

    m1 = Eigen::Matrix<T, 6, 6>::Random();
    m2 = Eigen::Matrix<T, 6, 8>::Random();

    for (auto _ : state) {
        benchmark::DoNotOptimize(res);

        res = m1 * m2;
    }
}
