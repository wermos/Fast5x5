#!/bin/bash
export REPEAT=10
export PROG="a.out"
export FILE="scal.txt"
export TIME=/usr/bin/time
export BOOST_SIMD_ROOT=/home/ping/These/boost.simd/include

rm -f custom_${FILE}
rm -f eigen_${FILE}

for size in $(seq 3 8); do
    g++ matrix_product_custom.cpp -I ${BOOST_SIMD_ROOT} -DSIZE=$size -O3 -march=native
    for i in $(seq 1 ${REPEAT}); do
        /usr/bin/time -f "%U, " ./a.out 2> >(tr -d '\n' | tee -a custom_${FILE}) && echo
    done
    echo >> custom_${FILE}

    g++ matrix_product_eigen.cpp -DSIZE=$size -O3 -march=native
    for i in $(seq 1 ${REPEAT}); do
        /usr/bin/time -f "%U, " ./a.out 2> >(tr -d '\n' | tee -a eigen_${FILE}) && echo
    done
    echo >> eigen_${FILE}
done
