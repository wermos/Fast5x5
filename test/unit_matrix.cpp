// Unitary tests for BaseMatrix class
#include <array>
#include <gtest/gtest.h>

#include "../fast_matrix.hpp"

TEST(BaseMatrixInstanciation, NoArguments) {
    const std::array<float, 6> null_matrix = {0, 0, 0, 0, 0, 0};
    BaseMatrix<float, 2, 3> no_args_matrix;
    ASSERT_EQ(no_args_matrix.dump_array(), null_matrix);
    EXPECT_TRUE(no_args_matrix.is_padding_zero());
}

TEST(BaseMatrixInstanciation, ScalarArguments) {
    const std::array<float, 9> diag_matrix = {5, 0, 0, 0, 5, 0, 0, 0, 5};
    BaseMatrix<float, 3, 3> scalar_arg_matrix(5);
    ASSERT_EQ(scalar_arg_matrix.dump_array(), diag_matrix);
    EXPECT_TRUE(scalar_arg_matrix.is_padding_zero());
}

TEST(BaseMatrixInstanciation, ArrayArguments) {
    const std::array<float, 6> array = {1, 2, 3, 4, 5, 6};
    BaseMatrix<float, 3, 2> array_3x2_float_matrix(&array[0]);
    ASSERT_EQ(array_3x2_float_matrix.dump_array(), array);
    EXPECT_TRUE(array_3x2_float_matrix.is_padding_zero());
    BaseMatrix<float, 2, 3> array_2x3_float_matrix(&array[0]);
    ASSERT_EQ(array_2x3_float_matrix.dump_array(), array);
    BaseMatrix<float, 1, 6> array_1x6_float_matrix(&array[0]);
    ASSERT_EQ(array_1x6_float_matrix.dump_array(), array);
    BaseMatrix<float, 6, 1> array_6x1_float_matrix(&array[0]);
    ASSERT_EQ(array_6x1_float_matrix.dump_array(), array);

    const std::array<float, 16> squared_array = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
    BaseMatrix<float, 4, 4> array_4x4_float_matrix(&squared_array[0]);
    ASSERT_EQ(array_4x4_float_matrix.dump_array(), squared_array);

    const std::array<double, 6> double_array = {1, 2, 3, 4, 5, 6};
    BaseMatrix<double, 3, 2> array_3x2_double_matrix(&double_array[0]);
    ASSERT_EQ(array_3x2_double_matrix.dump_array(), double_array);
    EXPECT_TRUE(array_3x2_double_matrix.is_padding_zero());
}

TEST(BaseMatrixAssignment, ArrayRValue) {
    const std::array<float, 6> array = {1, 2, 3, 4, 5, 6};
    BaseMatrix<float, 3, 2> array_3x2_float_matrix;
    array_3x2_float_matrix = &array[0];
    ASSERT_EQ(array_3x2_float_matrix.dump_array(), array);
    EXPECT_TRUE(array_3x2_float_matrix.is_padding_zero());

    const std::array<float, 16> squared_array = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
    BaseMatrix<float, 4, 4> array_4x4_float_matrix;
    array_4x4_float_matrix = &squared_array[0];
    ASSERT_EQ(array_4x4_float_matrix.dump_array(), squared_array);
}

TEST(BaseMatrixAssignment, BaseMatrixRValue) {
    const std::array<float, 6> array_right_matrix = {1, 2, 3, 4, 5, 6};
    BaseMatrix<float, 3, 2> left_matrix;
    BaseMatrix<float, 3, 2> right_matrix(&array_right_matrix[0]);

    left_matrix = right_matrix;
    ASSERT_EQ(left_matrix.dump_array(), right_matrix.dump_array());
    EXPECT_TRUE(left_matrix.is_padding_zero());
}

TEST(BaseMatrixStore, StoreMethod) {
    const std::array<float, 6> array = {1, 2, 3, 4, 5, 6};
    std::array<float, 6> stored_array;
    BaseMatrix<float, 3, 2> array_3x2_float_matrix(&array[0]);
    array_3x2_float_matrix.store(&stored_array[0]);
    ASSERT_EQ(stored_array, array);
    EXPECT_TRUE(array_3x2_float_matrix.is_padding_zero());
    BaseMatrix<float, 2, 3> array_2x3_float_matrix(&array[0]);
    array_2x3_float_matrix.store(&stored_array[0]);
    ASSERT_EQ(stored_array, array);
    BaseMatrix<float, 1, 6> array_1x6_float_matrix(&array[0]);
    array_1x6_float_matrix.store(&stored_array[0]);
    ASSERT_EQ(stored_array, array);
    BaseMatrix<float, 6, 1> array_6x1_float_matrix(&array[0]);
    array_6x1_float_matrix.store(&stored_array[0]);
    ASSERT_EQ(stored_array, array);

    const std::array<float, 16> squared_array = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
    std::array<float, 16> squared_stored_array;
    BaseMatrix<float, 4, 4> array_4x4_float_matrix(&squared_array[0]);
    array_4x4_float_matrix.store(&squared_stored_array[0]);
    ASSERT_EQ(squared_stored_array, squared_array);

    const std::array<double, 6> double_array = {1, 2, 3, 4, 5, 6};
    std::array<double, 6> double_stored_array = {1, 2, 3, 4, 5, 6};
    BaseMatrix<double, 3, 2> array_3x2_double_matrix(&double_array[0]);
    array_3x2_double_matrix.store(&double_stored_array[0]);
    ASSERT_EQ(double_stored_array, double_array);
    EXPECT_TRUE(array_3x2_double_matrix.is_padding_zero());

}
