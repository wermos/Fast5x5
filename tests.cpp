#include<iostream>
#include"fast_matrix.hpp"

template <typename T>
void print_matrix(T* matrix, int n, int m) {
    for (int i=0; i<n; i++) {
        for (int j=0; j<m; j++) {
            std::cout << matrix[i*m+j] << (j == m-1 ? "" : ", ");
        }
        std::cout << std::endl;
    }
}

void test_protect_for_division() {
    alignas(32) float input[8] {1,2,3,4,5,0,0,0};
    alignas(32) float output[8];
    alignas(32) float truth[8] {1,2,3,4,5,1,1,1};

    using pack_t = bs::pack<float, 8>;
    pack_t vector(&input[0]);
    protect_for_division<pack_t, 5>(vector);
    bs::aligned_store(vector, output);

    std::cout << "Testing: Protect for division" << std::endl;
    std::cout << "\tOutput: " << vector << std::endl;
    std::cout << "\tTruth: " << pack_t(&truth[0]) << std::endl;
    std::cout << std::endl;

    for (int i=0; i<8; i++) {
        assert(output[i] == truth[i]);
    }
}

void test_matrix_add() {
    alignas(32) float input_a[3*3] = {
        1, 2, 0,
        2, 5, 1,
        1, 1, 0.1,
    };

    alignas(32) float input_b[3*3] = {
        2, 2, 4,
        1, 0, 0.5,
        1, 1, 2,
    };

    alignas(32) float truth[3*3] = {
        3, 4, 4,
        3, 5, 1.5,
        2, 2, 2.1,
    };

    BaseMatrix<float, 3, 8> A(input_a), B(input_b), C;
    matrix_add(A, B, C);
    float* output = C.dump_array();


    std::cout << "Testing: Matrix Add" << std::endl;
    std::cout << "\tOutput: " << std::endl;
    print_matrix<float>(output, 3, 3);
    std::cout << std::endl;
    std::cout << "\tTruth: " << std::endl;
    print_matrix<float>(truth, 3, 3);
    std::cout << std::endl;

}

void test_matrix_sub() {
    alignas(32) float input_a[3*3] = {
        1, 2, 0,
        2, 5, 1,
        1, 1, 0.1,
    };

    alignas(32) float input_b[3*3] = {
        2, 2, 4,
        1, 0, 0.5,
        1, 1, 2,
    };

    alignas(32) float truth[3*3] = {
        -1, 0, -4,
        1, 5, 0.5,
        0, 0, -1.9,
    };

    BaseMatrix<float, 3, 8> A(input_a), B(input_b), C;
    matrix_sub(A, B, C);
    float* output = C.dump_array();


    std::cout << "Testing: Matrix sub" << std::endl;
    std::cout << "\tOutput: " << std::endl;
    print_matrix<float>(output, 3, 3);
    std::cout << std::endl;
    std::cout << "\tTruth: " << std::endl;
    print_matrix<float>(truth, 3, 3);
    std::cout << std::endl;

}

void test_matrix_mul_m_m() {
    alignas(32) float input_a[3*3] = {
        1, 2, 0,
        2, 5, 1,
        1, 1, 0.1,
    };

    alignas(32) float input_b[3*3] = {
        2, 2, 4,
        1, 0, 0.5,
        1, 1, 2,
    };

    alignas(32) float truth[3*3] = {
        4, 2, 5,
        10, 5, 12.5,
        3.1, 2.1, 4.7,
    };

    BaseMatrix<float, 3, 8> A(input_a), B(input_b), C;
    matrix_mul_m_m(A, B, C);
    float* output = C.dump_array();


    std::cout << "Testing: Matrix Mul M M" << std::endl;
    std::cout << "\tOutput: " << std::endl;
    print_matrix<float>(output, 3, 3);
    std::cout << std::endl;
    std::cout << "\tTruth: " << std::endl;
    print_matrix<float>(truth, 3, 3);
    std::cout << std::endl;

}

void test_column_dot_product() {
    alignas(32) float input_a[3*3] = {
        1, 2, 0,
        2, 5, 1,
        1, 1, 3,
    };

    alignas(32) float input_b[3*3] = {
        2, 2, 4,
        1, 0, 2,
        1, 1, 2,
    };

    alignas(32) float truth[4] = {
        5, 5, 8, 0,
    };

    using pack_t = bs::pack<float, 4>;
    BaseMatrix<float, 3, 4> A(input_a), B(input_b);
    pack_t output = column_dot_product(A, B);

    std::cout << "Testing: Column dot product" << std::endl;
    std::cout << "\tOutput: " << output << std::endl;
    std::cout << "\tTruth: " << pack_t(&truth[0]) << std::endl;
    std::cout << std::endl;
}

void test_column_scalar_product() {
    alignas(32) float scalar[4] = {
        1, 2, 3, 4,
    };

    alignas(32) float input_a[3*3] = {
        1, 2, 0,
        2, 5, 1,
        1, 1, 0.1,
    };

    alignas(32) float truth[3*3] = {
        1, 4, 0,
        2, 10, 3,
        1, 2, 0.3,
    };

    using pack_t = bs::pack<float, 4>;

    BaseMatrix<float, 3, 4> A(input_a), B, C;
    pack_t vector(&scalar[0]);
    column_scalar_product(vector, A, B);
    float* output = B.dump_array();


    std::cout << "Testing: Column scalar product" << std::endl;
    std::cout << "\tOutput: " << std::endl;
    print_matrix<float>(output, 3, 3);
    std::cout << std::endl;
    std::cout << "\tTruth: " << std::endl;
    print_matrix<float>(truth, 3, 3);
    std::cout << std::endl;

}

void test_identity() {
    IdentityMatrix<float, 5, 8> A;
    std::cout << "Testing identity matrix" << std::endl;
    std::cout << A;
}

int main(int argc, char **argv) {
    test_protect_for_division();
    test_matrix_add();
    test_matrix_sub();
    test_matrix_mul_m_m();
    test_column_dot_product();
    test_column_scalar_product();
    test_identity();
    return 0;
}
