// Unitary tests for inversion
#include <array>
#include <gtest/gtest.h>
#include <gtest/gtest-spi.h>
#include <cstdio>
#include <iomanip>

#include "../fast_matrix.hpp"


template <int size>
bool compare_float_array(const std::array<float, size> a, const std::array<float, size> b) {
    bool is_equal = false;
    return is_equal;
}

TEST(Inverse, Cholesky) {
    const std::array<float, 9> base_easy_float_array = {
        14, 8, 3,
        8, 5, 2,
        3, 2, 1,
    };

    const std::array<float, 9> result_easy_float_array =  {
        1, -2, 1,
        -2, 5, -4,
        1, -4, 6,
    };

    BaseMatrix<float, 3, 3, 8> base_easy_float_mat(&base_easy_float_array[0]);
    BaseMatrix<float, 3, 3, 8> inverse_easy_float_mat;

    Inverse<float, 3, 3, 8>::inverse(base_easy_float_mat, inverse_easy_float_mat);
    //EXPECT_PRED(compare_float_array<9>, inverse_easy_float_mat.dump_array(), result_easy_float_array);

    const std::array<float, 9> base_harder_float_array = {
        14, 16, 11,
        16, 21, 10,
        11, 10, 25,
    };

    const std::array<float, 9> result_harder_float_array =  {
        425./529, -290./529, -71./529,
        -290./529, 229./529, 36./529,
        -71./529, 36./529, 38./529,
    };

}
