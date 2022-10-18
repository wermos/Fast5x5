#pragma once

#include "Eigen/Dense"
#include "benchmark/benchmark.h"
#include "benchmarks/shared/common.hpp"

template<int SIZE = 8, typename T = float>
static void inversion_eigen(benchmark::State& state) {
    Eigen::Matrix<T, SIZE, SIZE> m, res;

    m1 = Eigen::Matrix<T, SIZE, SIZE>::Random();

    for (auto _ : state) {
        res = m.inverse();

        benchmark::DoNotOptimize(res);
    }
}
