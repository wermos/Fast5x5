#ifndef COMMON_HPP
#define COMMON_HPP

#include <cstddef> // for the std::size_t type
#include "benchmarks/shared/random.hpp"
#include "blaze/Math.h"
#include "fast5x5/fast5x5.hpp"

static constexpr int repetitions = 20;

template <typename T, std::size_t Rows, std::size_t Columns>
inline blaze::StaticMatrix<T, Rows, Columns> genRandomBlazeSymMat() {
	 blaze::StaticMatrix<T, Rows, Columns, blaze::rowMajor> m;

    for (int i = 0; i < Rows; i++) {
        for (int j = 0; j < Columns - i; j++) {
            m(i, j) = randomEntry<T>(-1.0, 1.0);
            m(j, i) = m(i, j);
        }
    }

	return m;
}

template <typename T, std::size_t Rows, std::size_t Columns>
inline blaze::StaticMatrix<T, Rows, Columns> genRandomBlazeMat() {
	blaze::StaticMatrix<T, Rows, Columns, blaze::rowMajor> m;

    m =
        blaze::generate(Rows, Columns, [](std::size_t i, std::size_t j) { return randomEntry<T>(-1.0, 1.0); });

	return m;
}

template <typename T, std::size_t Rows, std::size_t Columns>
inline BaseMatrix<T, Rows, Columns> genRandomCustomMat() {
	alignas(32) T a[Rows * Columns];

    for (int i = 0; i < Rows; i++) {
        for (int j = 0; j < Columns; j++) {
            a[i * Columns + j] = randomEntry<T>(-1.0, 1.0);
        }
    }

	return {a};
}

template <typename T, std::size_t Rows, std::size_t Columns>
inline BaseMatrix<T, Rows, Columns> genRandomCustomSymMat() {
	alignas(32) T a[Rows * Columns];

    for (int i = 0; i < Rows; i++) {
        for (int j = 0; j < Columns; j++) {
			// filling the upper triangle
            a[i * Columns + j] = randomEntry<T>(-1.0, 1.0);
            // copying the upper triangle element into
            // the lower triangle
            a[j * Columns + i] = a[i * Columns + j];
        }
    }

	return {a};
}

#endif // COMMON_HPP
