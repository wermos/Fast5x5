#!/bin/bash

export REPEAT=20
export PROG="a.out"
export FILE="gemm"
export TIME=/usr/bin/time

rm -f ${FILE}_simple.res
rm -f ${FILE}_eigen.res
rm -f ${FILE}_custom.res

for size in $(seq 3 8); do
    echo "Size=$size"

    echo -e "\t Simple"
    g++ gemm_simple.cpp -DSIZE=$size -O3 -march=native
    for i in $(seq 1 ${REPEAT}); do
        ${TIME} -f "%U, " ./a.out 2> >(tr -d '\n' | tee -a ${FILE}_simple.res) && echo
    done
    echo >> ${FILE}_simple.res

    echo -e "\t Eigen"
    g++ gemm_eigen.cpp -DSIZE=$size -O3 -march=native
    for i in $(seq 1 ${REPEAT}); do
        ${TIME} -f "%U, " ./a.out 2> >(tr -d '\n' | tee -a ${FILE}_eigen.res) && echo
    done
    echo >> ${FILE}_eigen.res

    echo -e "\t Custom"
    g++ gemm_custom.cpp -I ${BOOST_SIMD_ROOT} -DSIZE=$size -O3 -march=native
    for i in $(seq 1 ${REPEAT}); do
        ${TIME} -f "%U, " ./a.out 2> >(tr -d '\n' | tee -a ${FILE}_custom.res) && echo
    done
    echo >> ${FILE}_custom.res

done
