#ifndef SIMILARITY_EIGEN_H
#define SIMILARITY_EIGEN_H

#include "Eigen/Dense"
#include "benchmark/benchmark.h"
#include "benchmarks/shared/common.hpp"

static void similarity_eigen(benchmark::State& state) {
    Eigen::Matrix<float, SIZE, SIZE> m1, m2, res;

    m1 = Eigen::Matrix<float, SIZE, SIZE>::Random();
    m2 = Eigen::Matrix<float, SIZE, SIZE>::Random();

    for (auto _ : state) {
        benchmark::DoNotOptimize(res);

        res = m1 * m2 * m1.transpose();
    }
}

#endif // SIMILARITY_EIGEN_H
