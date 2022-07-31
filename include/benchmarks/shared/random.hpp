#ifndef RANDOM_HPP
#define RANDOM_HPP

#include <random>
#include <limits>

inline double randomDouble(double min, double max) {
    // Returns a random real in [min, max].
    static std::uniform_real_distribution<double> distribution(
        min, std::nextafter(max, std::numeric_limits<double>::infinity()));

    static std::mt19937_64 generator;

    return distribution(generator);
}

inline float randomFloat(float min, float max) {
    // Returns a random real in [min, max].
    static std::uniform_real_distribution<float> distribution(
        min, std::nextafter(max, std::numeric_limits<float>::infinity()));

    static std::mt19937_64 generator;

    return distribution(generator);
}

#endif // RANDOM_HPP
