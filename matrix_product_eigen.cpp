#include<eigen3/Eigen/Dense>
#include<iostream>


#ifndef SIZE
#define SIZE 4
#endif

int main(int argc, char **argv) {
    Eigen::Matrix<float, SIZE, SIZE> pa, pb, pf;

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

//    std::cout << pa << std::endl;
//    std::cout << pb << std::endl;

    for (unsigned int i=0; i<200000000; i++) {
        pf = pb * pa;
        pa = pb * pf;
    }

    std::cout << pa << std::endl;
    return 0;
}
