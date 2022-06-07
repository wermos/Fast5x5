#ifndef GEMM_CUSTOM_H
#define GEMM_CUSTOM_H

#include "benchmark/benchmark.h"
#include "fast5x5/fast5x5.hpp"
#include "gemm_header.h"

static void gemm_custom(benchmark::State& state) {
    alignas(32) float a[SIZE * SIZE];
    alignas(32) float b[SIZE * SIZE];

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            a[i * SIZE + j] = i + j;
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
            b[i * SIZE + j] = val;
        }
    }

    using M = BaseMatrix<float, SIZE, SIZE>;
    M pa(a), pb(b), pc;

    for (auto _ : state) {
        benchmark::DoNotOptimize(pc);

		matrix_mul_m_m(pa, pb, pc);
		matrix_mul_m_m(pb, pc, pa);

        // std::cout << pa << std::endl;
    }
}

#endif  // GEMM_CUSTOM_H
