// Unitary tests for arithmetics operators
#include <array>
#include <gtest/gtest.h>

#include "../fast_matrix.hpp"

TEST(MatrixAdd, Square) {
    const std::array<float, 9> base_float_array =  {1,2,3,4,5,6,7,8,9};
    const std::array<float, 9> add_float_array =  {1,1,1,1,1,1,1,1,1};
    const std::array<float, 9> result_float_array =  {2,3,4,5,6,7,8,9,10};

    BaseMatrix<float, 3, 3> base_float_mat(&base_float_array[0]);
    BaseMatrix<float, 3, 3> add_float_mat(&add_float_array[0]);
    BaseMatrix<float, 3, 3> result_float_mat;

    matrix_add(base_float_mat, add_float_mat, result_float_mat);
    EXPECT_EQ(result_float_mat.dump_array(), result_float_array);
    EXPECT_TRUE(result_float_mat.is_padding_zero());

    const std::array<double, 9> base_double_array =  {1,2,3,4,5,6,7,8,9};
    const std::array<double, 9> add_double_array =  {1,1,1,1,1,1,1,1,1};
    const std::array<double, 9> result_double_array =  {2,3,4,5,6,7,8,9,10};

    BaseMatrix<double, 3, 3> base_double_mat(&base_double_array[0]);
    BaseMatrix<double, 3, 3> add_double_mat(&add_double_array[0]);
    BaseMatrix<double, 3, 3> result_double_mat;

    matrix_add(base_double_mat, add_double_mat, result_double_mat);
    EXPECT_EQ(result_double_mat.dump_array(), result_double_array);
    EXPECT_TRUE(result_double_mat.is_padding_zero());
}

TEST(MatrixAdd, Rectangular2x3) {
    const std::array<float, 6> base_float_array =  {1,2,3,4,5,6};
    const std::array<float, 6> add_float_array =  {1,1,1,1,1,1};
    const std::array<float, 6> result_float_array =  {2,3,4,5,6,7};

    BaseMatrix<float, 2, 3> base_float_mat(&base_float_array[0]);
    BaseMatrix<float, 2, 3> add_float_mat(&add_float_array[0]);
    BaseMatrix<float, 2, 3> result_float_mat;

    matrix_add(base_float_mat, add_float_mat, result_float_mat);
    EXPECT_EQ(result_float_mat.dump_array(), result_float_array);
    EXPECT_TRUE(result_float_mat.is_padding_zero());

    const std::array<double, 6> base_double_array =  {1,2,3,4,5,6};
    const std::array<double, 6> add_double_array =  {1,1,1,1,1,1};
    const std::array<double, 6> result_double_array =  {2,3,4,5,6,7};

    BaseMatrix<double, 2, 3> base_double_mat(&base_double_array[0]);
    BaseMatrix<double, 2, 3> add_double_mat(&add_double_array[0]);
    BaseMatrix<double, 2, 3> result_double_mat;

    matrix_add(base_double_mat, add_double_mat, result_double_mat);
    EXPECT_EQ(result_double_mat.dump_array(), result_double_array);
    EXPECT_TRUE(result_double_mat.is_padding_zero());
}

TEST(MatrixSub, Square) {
    const std::array<float, 9> base_float_array =  {1,2,3,4,5,6,7,8,9};
    const std::array<float, 9> sub_float_array =  {1,1,1,1,1,1,1,1,1};
    const std::array<float, 9> result_float_array =  {0,1,2,3,4,5,6,7,8};

    BaseMatrix<float, 3, 3> base_float_mat(&base_float_array[0]);
    BaseMatrix<float, 3, 3> sub_float_mat(&sub_float_array[0]);
    BaseMatrix<float, 3, 3> result_float_mat;

    matrix_sub(base_float_mat, sub_float_mat, result_float_mat);
    EXPECT_EQ(result_float_mat.dump_array(), result_float_array);
    EXPECT_TRUE(result_float_mat.is_padding_zero());

    const std::array<double, 9> base_double_array =  {1,2,3,4,5,6,7,8,9};
    const std::array<double, 9> sub_double_array =  {1,1,1,1,1,1,1,1,1};
    const std::array<double, 9> result_double_array =  {0,1,2,3,4,5,6,7,8};

    BaseMatrix<double, 3, 3> base_double_mat(&base_double_array[0]);
    BaseMatrix<double, 3, 3> sub_double_mat(&sub_double_array[0]);
    BaseMatrix<double, 3, 3> result_double_mat;

    matrix_sub(base_double_mat, sub_double_mat, result_double_mat);
    EXPECT_EQ(result_double_mat.dump_array(), result_double_array);
    EXPECT_TRUE(result_double_mat.is_padding_zero());
}

TEST(MatrixSub, Rectangular2x3) {
    const std::array<float, 6> base_float_array =  {1,2,3,4,5,6};
    const std::array<float, 6> sub_float_array =  {1,1,1,1,1,1};
    const std::array<float, 6> result_float_array =  {0,1,2,3,4,5};

    BaseMatrix<float, 2, 3> base_float_mat(&base_float_array[0]);
    BaseMatrix<float, 2, 3> sub_float_mat(&sub_float_array[0]);
    BaseMatrix<float, 2, 3> result_float_mat;

    matrix_sub(base_float_mat, sub_float_mat, result_float_mat);
    EXPECT_EQ(result_float_mat.dump_array(), result_float_array);
    EXPECT_TRUE(result_float_mat.is_padding_zero());

    const std::array<double, 6> base_double_array =  {1,2,3,4,5,6};
    const std::array<double, 6> sub_double_array =  {1,1,1,1,1,1};
    const std::array<double, 6> result_double_array =  {0,1,2,3,4,5};

    BaseMatrix<double, 2, 3> base_double_mat(&base_double_array[0]);
    BaseMatrix<double, 2, 3> sub_double_mat(&sub_double_array[0]);
    BaseMatrix<double, 2, 3> result_double_mat;

    matrix_sub(base_double_mat, sub_double_mat, result_double_mat);
    EXPECT_EQ(result_double_mat.dump_array(), result_double_array);
    EXPECT_TRUE(result_double_mat.is_padding_zero());
}

TEST(MatrixMulMM, Square) {
    const std::array<float, 9> left_float_array = {
        1, 2, 0,
        2, 5, 1,
        1, 1, 0.1,
    };
    const std::array<float, 9> right_float_array = {
        2, 2, 4,
        1, 0, 0.5,
        1, 1, 2,
    };
    const std::array<float, 9> result_float_array = {
        4, 2, 5,
        10, 5, 12.5,
        3.1, 2.1, 4.7,
    };

    BaseMatrix<float, 3, 3> left_float_mat(&left_float_array[0]);
    BaseMatrix<float, 3, 3> right_float_mat(&right_float_array[0]);
    BaseMatrix<float, 3, 3> result_float_mat;

    matrix_mul_m_m(left_float_mat, right_float_mat, result_float_mat);
    EXPECT_EQ(result_float_mat.dump_array(), result_float_array);
    EXPECT_TRUE(result_float_mat.is_padding_zero());

    const std::array<double, 9> left_double_array = {
        1, 2, 0,
        2, 5, 1,
        1, 1, 0.1,
    };
    const std::array<double, 9> right_double_array = {
        2, 2, 4,
        1, 0, 0.5,
        1, 1, 2,
    };
    const std::array<double, 9> result_double_array = {
        4, 2, 5,
        10, 5, 12.5,
        3.1, 2.1, 4.7,
    };

    BaseMatrix<double, 3, 3> left_double_mat(&left_double_array[0]);
    BaseMatrix<double, 3, 3> right_double_mat(&right_double_array[0]);
    BaseMatrix<double, 3, 3> result_double_mat;

    matrix_mul_m_m(left_double_mat, right_double_mat, result_double_mat);
    EXPECT_EQ(result_double_mat.dump_array(), result_double_array);
    EXPECT_TRUE(result_double_mat.is_padding_zero());
}

TEST(MatrixMulMM, Rectangular2x3t3x2) {
    const std::array<float, 6> left_float_array = {
        1, 2, 3,
        4, 5, 6,
    };
    const std::array<float, 6> right_float_array = {
        7, 8,
        9, 10,
        11, 12,
    };
    const std::array<float, 4> result_float_array = {
        58, 64,
        139, 154,
    };

    BaseMatrix<float, 2, 3> left_float_mat(&left_float_array[0]);
    BaseMatrix<float, 3, 2> right_float_mat(&right_float_array[0]);
    BaseMatrix<float, 2, 2> result_float_mat;

    matrix_mul_m_m(left_float_mat, right_float_mat, result_float_mat);
    EXPECT_EQ(result_float_mat.dump_array(), result_float_array);
    EXPECT_TRUE(result_float_mat.is_padding_zero());


    const std::array<double, 6> left_double_array = {
        1, 2, 3,
        4, 5, 6,
    };
    const std::array<double, 6> right_double_array = {
        7, 8,
        9, 10,
        11, 12,
    };
    const std::array<double, 4> result_double_array = {
        58, 64,
        139, 154,
    };

    BaseMatrix<double, 2, 3> left_double_mat(&left_double_array[0]);
    BaseMatrix<double, 3, 2> right_double_mat(&right_double_array[0]);
    BaseMatrix<double, 2, 2> result_double_mat;

    matrix_mul_m_m(left_double_mat, right_double_mat, result_double_mat);
    EXPECT_EQ(result_double_mat.dump_array(), result_double_array);
    EXPECT_TRUE(result_double_mat.is_padding_zero());
}

TEST(MatrixMulMM, Rectangular2x5t5x2) {
    const std::array<float, 10> left_float_array = {
        1, 2, 3, 4, 5,
        6, 7, 8, 9, 10,
    };

    const std::array<float, 10> right_float_array = {
        1, 2,
        3, 4,
        5, 6,
        7, 8,
        9, 10,
    };
    const std::array<float, 4> result_float_array = {
        95, 110,
        220, 260,
    };

    BaseMatrix<float, 2, 5> left_float_mat(&left_float_array[0]);
    BaseMatrix<float, 5, 2> right_float_mat(&right_float_array[0]);
    BaseMatrix<float, 2, 2> result_float_mat;

    matrix_mul_m_m(left_float_mat, right_float_mat, result_float_mat);
    EXPECT_EQ(result_float_mat.dump_array(), result_float_array);
    EXPECT_TRUE(result_float_mat.is_padding_zero());


    const std::array<double, 10> left_double_array = {
        1, 2, 3, 4, 5,
        6, 7, 8, 9, 10,
    };

    const std::array<double, 10> right_double_array = {
        1, 2,
        3, 4,
        5, 6,
        7, 8,
        9, 10,
    };
    const std::array<double, 4> result_double_array = {
        95, 110,
        220, 260,
    };

    BaseMatrix<double, 2, 5> left_double_mat(&left_double_array[0]);
    BaseMatrix<double, 5, 2> right_double_mat(&right_double_array[0]);
    BaseMatrix<double, 2, 2> result_double_mat;

    matrix_mul_m_m(left_double_mat, right_double_mat, result_double_mat);
    EXPECT_EQ(result_double_mat.dump_array(), result_double_array);
    EXPECT_TRUE(result_double_mat.is_padding_zero());
}

TEST(MatrixMulMtM, Square) {
    const std::array<float, 9> left_float_array = {
        1, 2, 1,
        2, 5, 1,
        0, 1, 0.1,
    };
    const std::array<float, 9> right_float_array = {
        2, 2, 4,
        1, 0, 0.5,
        1, 1, 2,
    };
    const std::array<float, 9> result_float_array = {
        4, 2, 5,
        10, 5, 12.5,
        3.1, 2.1, 4.7,
    };

    BaseMatrix<float, 3, 3> left_float_mat(&left_float_array[0]);
    BaseMatrix<float, 3, 3> right_float_mat(&right_float_array[0]);
    BaseMatrix<float, 3, 3> result_float_mat;

    matrix_mul_mt_m(left_float_mat, right_float_mat, result_float_mat);
    EXPECT_EQ(result_float_mat.dump_array(), result_float_array);
    EXPECT_TRUE(result_float_mat.is_padding_zero());

    const std::array<double, 9> left_double_array = {
        1, 2, 1,
        2, 5, 1,
        0, 1, 0.1,
    };
    const std::array<double, 9> right_double_array = {
        2, 2, 4,
        1, 0, 0.5,
        1, 1, 2,
    };
    const std::array<double, 9> result_double_array = {
        4, 2, 5,
        10, 5, 12.5,
        3.1, 2.1, 4.7,
    };

    BaseMatrix<double, 3, 3> left_double_mat(&left_double_array[0]);
    BaseMatrix<double, 3, 3> right_double_mat(&right_double_array[0]);
    BaseMatrix<double, 3, 3> result_double_mat;

    matrix_mul_mt_m(left_double_mat, right_double_mat, result_double_mat);
    EXPECT_EQ(result_double_mat.dump_array(), result_double_array);
    EXPECT_TRUE(result_double_mat.is_padding_zero());
}

TEST(MatrixMulMtM, Rectangular2x3t3x2) {
    const std::array<float, 6> left_float_array = {
        1, 4,
        2, 5,
        3, 6,
    };
    const std::array<float, 6> right_float_array = {
        7, 8,
        9, 10,
        11, 12,
    };
    const std::array<float, 4> result_float_array = {
        58, 64,
        139, 154,
    };

    BaseMatrix<float, 3, 2> left_float_mat(&left_float_array[0]);
    BaseMatrix<float, 3, 2> right_float_mat(&right_float_array[0]);
    BaseMatrix<float, 2, 2> result_float_mat;

    matrix_mul_mt_m(left_float_mat, right_float_mat, result_float_mat);
    EXPECT_EQ(result_float_mat.dump_array(), result_float_array);
    EXPECT_TRUE(result_float_mat.is_padding_zero());


    const std::array<double, 6> left_double_array = {
        1, 4,
        2, 5,
        3, 6,
    };
    const std::array<double, 6> right_double_array = {
        7, 8,
        9, 10,
        11, 12,
    };
    const std::array<double, 4> result_double_array = {
        58, 64,
        139, 154,
    };

    BaseMatrix<double, 3, 2> left_double_mat(&left_double_array[0]);
    BaseMatrix<double, 3, 2> right_double_mat(&right_double_array[0]);
    BaseMatrix<double, 2, 2> result_double_mat;

    matrix_mul_mt_m(left_double_mat, right_double_mat, result_double_mat);
    EXPECT_EQ(result_double_mat.dump_array(), result_double_array);
    EXPECT_TRUE(result_double_mat.is_padding_zero());
}

TEST(MatrixMulMMt, Square) {
    const std::array<float, 9> left_float_array = {
        1, 2, 0,
        2, 5, 1,
        1, 1, 0.1,
    };
    const std::array<float, 9> right_float_array = {
        2, 1, 1,
        2, 0, 1,
        4, 0.5, 2,
    };
    const std::array<float, 9> result_float_array = {
        4, 2, 5,
        10, 5, 12.5,
        3.1, 2.1, 4.7,
    };

    BaseMatrix<float, 3, 3> left_float_mat(&left_float_array[0]);
    BaseMatrix<float, 3, 3> right_float_mat(&right_float_array[0]);
    BaseMatrix<float, 3, 3> result_float_mat;

    matrix_mul_m_mt(left_float_mat, right_float_mat, result_float_mat);
    EXPECT_EQ(result_float_mat.dump_array(), result_float_array);
    EXPECT_TRUE(result_float_mat.is_padding_zero());

    const std::array<double, 9> left_double_array = {
        1, 2, 0,
        2, 5, 1,
        1, 1, 0.1,
    };
    const std::array<double, 9> right_double_array = {
        2, 1, 1,
        2, 0, 1,
        4, 0.5, 2,
    };
    const std::array<double, 9> result_double_array = {
        4, 2, 5,
        10, 5, 12.5,
        3.1, 2.1, 4.7,
    };

    BaseMatrix<double, 3, 3> left_double_mat(&left_double_array[0]);
    BaseMatrix<double, 3, 3> right_double_mat(&right_double_array[0]);
    BaseMatrix<double, 3, 3> result_double_mat;

    matrix_mul_m_mt(left_double_mat, right_double_mat, result_double_mat);
    EXPECT_EQ(result_double_mat.dump_array(), result_double_array);
    EXPECT_TRUE(result_double_mat.is_padding_zero());
}

TEST(MatrixMulMMt, Rectangular2x3t3x2) {
    const std::array<float, 6> left_float_array = {
        1, 2, 3,
        4, 5, 6,
    };
    const std::array<float, 6> right_float_array = {
        7, 9, 11,
        8, 10, 12
    };
    const std::array<float, 4> result_float_array = {
        58, 64,
        139, 154,
    };

    BaseMatrix<float, 2, 3> left_float_mat(&left_float_array[0]);
    BaseMatrix<float, 2, 3> right_float_mat(&right_float_array[0]);
    BaseMatrix<float, 2, 2> result_float_mat;

    matrix_mul_m_mt(left_float_mat, right_float_mat, result_float_mat);
    EXPECT_EQ(result_float_mat.dump_array(), result_float_array);
    EXPECT_TRUE(result_float_mat.is_padding_zero());


    const std::array<double, 6> left_double_array = {
        1, 2, 3,
        4, 5, 6,
    };
    const std::array<double, 6> right_double_array = {
        7, 9, 11,
        8, 10, 12
    };
    const std::array<double, 4> result_double_array = {
        58, 64,
        139, 154,
    };

    BaseMatrix<double, 2, 3> left_double_mat(&left_double_array[0]);
    BaseMatrix<double, 2, 3> right_double_mat(&right_double_array[0]);
    BaseMatrix<double, 2, 2> result_double_mat;

    matrix_mul_m_mt(left_double_mat, right_double_mat, result_double_mat);
    EXPECT_EQ(result_double_mat.dump_array(), result_double_array);
    EXPECT_TRUE(result_double_mat.is_padding_zero());
}
