#ifndef INVERSION_EIGEN_H
#define INVERSION_EIGEN_H

#include "Eigen/Dense"
#include "benchmark/benchmark.h"
#include "gemm_header.h"
#include "random.hpp"

static void inversion_eigen(benchmark::State& state) {
    Eigen::Matrix<float, SIZE, SIZE> m1, res;

    m1 = Eigen::Matrix<float, SIZE, SIZE>::Random();

    for (auto _ : state) {
        benchmark::DoNotOptimize(res);

        res = m1.inverse();
    }
}

#endif  // INVERSION_EIGEN_H
