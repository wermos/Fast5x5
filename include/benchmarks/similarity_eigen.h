#ifndef SIMILARITY_EIGEN_H
#define SIMILARITY_EIGEN_H

#include "Eigen/Dense"
#include "benchmark/benchmark.h"
#include "gemm_header.h"

static void similarity_eigen(benchmark::State& state) {
    Eigen::Matrix<double, SIZE, SIZE> m1, m2, res;

    m1 = Eigen::Matrix<double, SIZE, SIZE>::Random();
    m2 = Eigen::Matrix<double, SIZE, SIZE>::Random();

    for (auto _ : state) {
        benchmark::DoNotOptimize(res);

        res = m1 * m2 * m1.transpose();
    }
}

#endif  // SIMILARITY_EIGEN_H
