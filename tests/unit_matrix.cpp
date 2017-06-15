// Unitary tests for BaseMatrix class
#include <array>
#include <gtest/gtest.h>

#include "../fast_matrix.hpp"

TEST(BaseMatrixInstanciation, NoArguments) {
    const std::array<float, 6> null_matrix = {0, 0, 0, 0, 0, 0};
    BaseMatrix<float, 2, 3, 8> no_args_matrix;
    ASSERT_EQ(no_args_matrix.dump_array(), null_matrix);
}

TEST(BaseMatrixInstanciation, ScalarArguments) {
    const std::array<float, 9> diag_matrix = {5, 0, 0, 0, 5, 0, 0, 0, 5};
    BaseMatrix<float, 3, 3, 8> scalar_arg_matrix(5);
    ASSERT_EQ(scalar_arg_matrix.dump_array(), diag_matrix);
}

TEST(BaseMatrixInstanciation, ArrayArguments) {
    const std::array<float, 6> array = {1, 2, 3, 4, 5, 6};
    BaseMatrix<float, 3, 2, 8> array_3x2_float_matrix(&array[0]);
    ASSERT_EQ(array_3x2_float_matrix.dump_array(), array);
    BaseMatrix<float, 2, 3, 8> array_2x3_float_matrix(&array[0]);
    ASSERT_EQ(array_2x3_float_matrix.dump_array(), array);
    BaseMatrix<float, 1, 6, 8> array_1x6_float_matrix(&array[0]);
    ASSERT_EQ(array_1x6_float_matrix.dump_array(), array);
    BaseMatrix<float, 6, 1, 8> array_6x1_float_matrix(&array[0]);
    ASSERT_EQ(array_6x1_float_matrix.dump_array(), array);

    const std::array<double, 6> double_array = {1, 2, 3, 4, 5, 6};
    BaseMatrix<double, 3, 2, 8> array_3x2_double_matrix(&double_array[0]);
    ASSERT_EQ(array_3x2_double_matrix.dump_array(), double_array);
}

TEST(BaseMatrixAssignment, ArrayRValue) {
    const std::array<float, 6> array = {1, 2, 3, 4, 5, 6};
    BaseMatrix<float, 3, 2, 8> array_3x2_float_matrix;
    array_3x2_float_matrix = &array[0];
    ASSERT_EQ(array_3x2_float_matrix.dump_array(), array);
}

TEST(BaseMatrixAssignment, BaseMatrixRValue) {
    const std::array<float, 6> array_right_matrix = {1, 2, 3, 4, 5, 6};
    BaseMatrix<float, 3, 2, 8> left_matrix;
    BaseMatrix<float, 3, 2, 8> right_matrix(&array_right_matrix[0]);

    left_matrix = right_matrix;
    ASSERT_EQ(left_matrix.dump_array(), right_matrix.dump_array());
}
