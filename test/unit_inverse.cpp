// Unitary tests for inversion
#include <array>
#include <gtest/gtest.h>
#include <gtest/gtest-spi.h>
#include <cstdio>
#include <iomanip>
#include <cmath>

#include "../fast_matrix.hpp"


template <typename M>
::testing::AssertionResult compare_floating_point_matrices(const char* a_expr, const char* b_expr, M &a, M &b) {
    using my_type = typename M::ElementType;
    double precision = 1e-13;
    if (typeid(my_type) == typeid(float)) {
        precision = 5e-6;
    }
    bool is_equal = true;
    std::array<my_type, M::NRows * M::NCols> array_a = a.dump_array(); 
    std::array<my_type, M::NRows * M::NCols> array_b = b.dump_array();
    for (int i = 0; i<M::NRows*M::NCols; i++) {
        my_type diff = std::abs(array_a[i]-array_b[i]);
        my_type largest = (array_b[i] > array_a[i]) ? array_b[i] : array_a[i];
        if(diff > precision && diff > largest*precision) {
            is_equal = false;
            break;
        }
    }
    if (is_equal) {
        return ::testing::AssertionSuccess();
    } else {
        return ::testing::AssertionFailure() << a_expr << std::endl << a
            << "and " << b_expr << std::endl << b << " are not equal" << std::endl;
    }
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
    BaseMatrix<float, 3, 3, 8> result_easy_float_mat(&result_easy_float_array[0]);

    Inverse<float, 3, 3, 8>::inverse(base_easy_float_mat, inverse_easy_float_mat);
    EXPECT_PRED_FORMAT2(compare_floating_point_matrices, inverse_easy_float_mat, result_easy_float_mat);
    EXPECT_TRUE(inverse_easy_float_mat.is_padding_zero());

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

    BaseMatrix<float, 3, 3, 8> base_harder_float_mat(&base_harder_float_array[0]);
    BaseMatrix<float, 3, 3, 8> inverse_harder_float_mat;
    BaseMatrix<float, 3, 3, 8> result_harder_float_mat(&result_harder_float_array[0]);

    Inverse<float, 3, 3, 8>::inverse(base_harder_float_mat, inverse_harder_float_mat);
    EXPECT_PRED_FORMAT2(compare_floating_point_matrices, inverse_harder_float_mat, result_harder_float_mat);
    EXPECT_TRUE(inverse_harder_float_mat.is_padding_zero());



    const std::array<double, 9> base_easy_double_array = {
        14, 8, 3,
        8, 5, 2,
        3, 2, 1,
    };

    const std::array<double, 9> result_easy_double_array =  {
        1, -2, 1,
        -2, 5, -4,
        1, -4, 6,
    };

    BaseMatrix<double, 3, 3, 8> base_easy_double_mat(&base_easy_double_array[0]);
    BaseMatrix<double, 3, 3, 8> inverse_easy_double_mat;
    BaseMatrix<double, 3, 3, 8> result_easy_double_mat(&result_easy_double_array[0]);

    Inverse<double, 3, 3, 8>::inverse(base_easy_double_mat, inverse_easy_double_mat);
    EXPECT_PRED_FORMAT2(compare_floating_point_matrices, inverse_easy_double_mat, result_easy_double_mat);
    EXPECT_TRUE(inverse_easy_double_mat.is_padding_zero());

    const std::array<double, 9> base_harder_double_array = {
        14, 16, 11,
        16, 21, 10,
        11, 10, 25,
    };

    const std::array<double, 9> result_harder_double_array =  {
        425./529, -290./529, -71./529,
        -290./529, 229./529, 36./529,
        -71./529, 36./529, 38./529,
    };

    BaseMatrix<double, 3, 3, 8> base_harder_double_mat(&base_harder_double_array[0]);
    BaseMatrix<double, 3, 3, 8> inverse_harder_double_mat;
    BaseMatrix<double, 3, 3, 8> result_harder_double_mat(&result_harder_double_array[0]);

    Inverse<double, 3, 3, 8>::inverse(base_harder_double_mat, inverse_harder_double_mat);
    EXPECT_PRED_FORMAT2(compare_floating_point_matrices, inverse_harder_double_mat, result_harder_double_mat);
    EXPECT_TRUE(inverse_harder_double_mat.is_padding_zero());
}
