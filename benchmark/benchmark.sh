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
        # GNU time produces its data on stderr, and we want to post-process it.
        # But bash's pipe operator only works on stdout. So we need to swap
        # stdout and stderr first.
        /usr/bin/time -f "%U, " ./a.out 3>&1 1>&2 2>&3 3>&-                    \
                    | tr -d '\n' | tee -a ${FILE}_simple.res                   \
        && echo
    done
    echo >> ${FILE}_simple.res

    echo -e "\t Eigen"
    g++ gemm_eigen.cpp -DSIZE=$size -O3 -march=native
    for i in $(seq 1 ${REPEAT}); do
        # Same as above, only targeting a different file
        /usr/bin/time -f "%U, " ./a.out 3>&1 1>&2 2>&3 3>&-                    \
                    | tr -d '\n' | tee -a ${FILE}_eigen.res                    \
        && echo
    done
    echo >> ${FILE}_eigen.res

    echo -e "\t Custom"
    g++ gemm_custom.cpp -DSIZE=$size -O3 -march=native
    for i in $(seq 1 ${REPEAT}); do
        # Same as above, only targeting a different file
        /usr/bin/time -f "%U, " ./a.out 3>&1 1>&2 2>&3 3>&-                    \
                    | tr -d '\n' | tee -a ${FILE}_custom.res                   \
        && echo
    done
    echo >> ${FILE}_custom.res

done
