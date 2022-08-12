#pragma once

#include <random>
#include <limits>

template<typename T>
inline T randomEntry(T min, T max) {
    // Returns a random real in [min, max].
    static std::uniform_real_distribution<T> distribution(
        min, std::nextafter(max, std::numeric_limits<T>::infinity()));

    static std::mt19937_64 generator;

    return distribution(generator);
}
