#ifndef GEMM_EIGEN_H
#define GEMM_EIGEN_H

#include "Eigen/Dense"
#include "benchmark/benchmark.h"
#include "gemm_header.h"

static void gemm_eigen(benchmark::State& state) {
    Eigen::Matrix<float, SIZE, SIZE> pa, pb, pc;

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            pa(i, j) = i + j;
        }
    }

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            float val;
            if (i == 0 && j == 1)
                val = -1;
            else if (i == 1 && j == 0)
                val = 1;
            else if (i > 1 && i == j && i % 2)
                val = -1;
            else if (i > 1 && i == j && !(i % 2))
                val = 1;
            else
                val = 0;
            pb(i, j) = val;
        }
    }

    for (auto _ : state) {
        benchmark::DoNotOptimize(pc);

		pc = pa * pb;
		pa = pb * pc;

        // std::cout << pa << std::endl;
    }
}

#endif  // GEMM_EIGEN_H
