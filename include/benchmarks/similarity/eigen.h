#ifndef SIMILARITY_EIGEN_H
#define SIMILARITY_EIGEN_H

#include "Eigen/Dense"
#include "benchmark/benchmark.h"
#include "benchmarks/shared/common.hpp"

template<int SIZE = 8, typename T = float>
static void similarity_eigen(benchmark::State& state) {
    Eigen::Matrix<T, SIZE, SIZE> m1, m2, res;

    m1 = Eigen::Matrix<T, SIZE, SIZE>::Random();
    m2 = Eigen::Matrix<T, SIZE, SIZE>::Random();

    for (auto _ : state) {
        benchmark::DoNotOptimize(res);

        res = m1 * m2 * m1.transpose();
    }
}

#endif // SIMILARITY_EIGEN_H
