// Unitary tests for BaseMatrix class
#include <gtest/gtest.h>

#include <array>

#include "fast5x5/fast5x5.hpp"

TEST(VectorInstantiation, NoArguments) {
    const std::array<float, 5> null_vector = {0, 0, 0, 0, 0};
    Vector<float, 5> no_args_vector;
    ASSERT_EQ(no_args_vector.dump_array(), null_vector);
    EXPECT_TRUE(no_args_vector.is_padding_zero());
}

TEST(VectorInstantiation, ArrayArguments) {
    const std::array<float, 6> float_array = {1, 2, 3, 4, 5, 6};
    Vector<float, 6> float_vector(&float_array[0]);
    ASSERT_EQ(float_vector.dump_array(), float_array);
    EXPECT_TRUE(float_vector.is_padding_zero());

    const std::array<double, 4> double_array = {1, 2, 3, 4};
    Vector<double, 4> double_vector(&double_array[0]);
    ASSERT_EQ(double_vector.dump_array(), double_array);
    EXPECT_TRUE(double_vector.is_padding_zero());
}

TEST(VectorAssignment, ArrayRValue) {
    const std::array<float, 6> array = {1, 2, 3, 4, 5, 6};
    Vector<float, 6> float_vector;
    float_vector = &array[0];
    ASSERT_EQ(float_vector.dump_array(), array);
    EXPECT_TRUE(float_vector.is_padding_zero());
}

TEST(VectorAssignment, VectorRValue) {
    const std::array<float, 6> array_right_vector = {1, 2, 3, 4, 5, 6};
    Vector<float, 6> left_vector;
    Vector<float, 6> right_vector(&array_right_vector[0]);

    left_vector = right_vector;
    ASSERT_EQ(left_vector.dump_array(), right_vector.dump_array());
    EXPECT_TRUE(left_vector.is_padding_zero());
}

TEST(MatrixVectorProduct, SimpleProduct) {
    const std::array<float, 6> matrix_array = {
        1, -1, 2, 0, -3, 1,
    };
    const std::array<float, 3> vector_array = {2, 1, 0};
    const std::array<float, 2> result_array = {1, -3};

    BaseMatrix<float, 2, 3> matrix(&matrix_array[0]);
    Vector<float, 3> vector(&vector_array[0]);
    Vector<float, 2> result_vector;

    matrix_mul_m_v(matrix, vector, result_vector);
    ASSERT_EQ(result_vector.dump_array(), result_array);
    EXPECT_TRUE(result_vector.is_padding_zero());
}
