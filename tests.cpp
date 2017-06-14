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

    BaseMatrix<float, 3, 3, 8> A(input_a), B(input_b), C;
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

    BaseMatrix<float, 3, 3, 8> A(input_a), B(input_b), C;
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

    BaseMatrix<float, 3, 3, 8> A(input_a), B(input_b), C;
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

void test_identity() {
    //IdentityMatrix<float, 5, 8> A;
    BaseMatrix<float, 5, 5, 8> A(1);
    std::cout << "Testing identity matrix" << std::endl;
    std::cout << A;
}

void test_matrix_inv() {
    alignas(32) float input[3*3] = {
        1, 0, 0,
        0, 2, 0,
        0, 0, 4,
    };
    alignas(32) float truth[3*3] = {
        1, 0, 0,
        0, 0.5, 0,
        0, 0, 0.25,
    };

    BaseMatrix<float, 3, 3, 4> A(input), I;
    Inverse<float, 3, 3, 4>::inverse(A, I);
    std::cout << "Testing Matrix inversion" << std::endl;
    std::cout << "\tOutput: " << std::endl;
    print_matrix<float>(I.dump_array(), 3, 3);
    std::cout << "\tTruth: " << std::endl;
    print_matrix<float>(truth, 3, 3);
    std::cout << std::endl;
}

int main(int argc, char **argv) {
    test_matrix_add();
    test_matrix_sub();
    test_matrix_mul_m_m();
    test_identity();
    test_matrix_inv();
    return 0;
}
