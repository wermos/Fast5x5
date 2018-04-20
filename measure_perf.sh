#!/bin/bash
export REPEAT=10
export PROG="a.out"
export FILE="scal.txt"
export TIME=/usr/bin/time

rm -f custom_${FILE}
rm -f eigen_${FILE}

for size in $(seq 3 8); do
    g++ matrix_product_custom.cpp -DSIZE=$size -O3 -march=native
    for i in $(seq 1 ${REPEAT}); do
        # GNU time produces its data on stderr, and we want to post-process it.
        # But bash's pipe operator only works on stdout. So we need to swap
        # stdout and stderr first.
        /usr/bin/time -f "%U, " ./a.out 3>&1 1>&2 2>&3 3>&-                    \
                    | tr -d '\n' | tee -a custom_${FILE}                       \
        && echo
    done
    echo >> custom_${FILE}

    g++ matrix_product_eigen.cpp -DSIZE=$size -O3 -march=native
    for i in $(seq 1 ${REPEAT}); do
        # Same as above, only targeting a different file
        /usr/bin/time -f "%U, " ./a.out 3>&1 1>&2 2>&3 3>&-                    \
                    | tr -d '\n' | tee -a eigen_${FILE}                        \
        && echo
    done
    echo >> eigen_${FILE}
done
