#ifndef GEMM_BLAZE_H
#define GEMM_BLAZE_H

#include "benchmark/benchmark.h"
#include "blaze/Math.h"
#include "gemm_header.h"

static void gemm_blaze(benchmark::State& state) {
    blaze::StaticMatrix<float, SIZE, SIZE, blaze::rowMajor> pa, pb, pc;

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

#endif  // GEMM_BLAZE_H
