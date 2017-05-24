#include<eigen3/Eigen/Dense>
#include<iostream>

#include "gemm_header.h"


int main(int argc, char **argv) {
    Eigen::Matrix<float, SIZE, SIZE> pa, pb, pc;

    for (int i=0; i<SIZE; i++) {
        for (int j=0; j<SIZE; j++) {
            pa(i,j) = i+j;
        }
    }

    for (int i=0; i<SIZE; i++) {
        for (int j=0; j<SIZE; j++) {
            float val;
            if (i == 0 && j == 1) val = -1;
            else if (i == 1 && j == 0) val = 1;
            else if (i > 1 && i == j && i % 2) val = -1;
            else if (i > 1 && i == j && !(i % 2)) val = 1;
            else val = 0;
            pb(i,j) = val;
        }
    }

    for (unsigned int i=0; i < REPEAT; i++) {
        pc = pa * pb;
        pa = pb * pc;
    }

    std::cout << pa << std::endl;
    return 0;
}
