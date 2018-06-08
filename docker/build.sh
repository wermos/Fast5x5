#!/bin/bash
tar xvfJ boost.simd.tar.xz
docker build -t gitlab-registry.in2p3.fr/chamont/fast5x5 .
docker push gitlab-registry.in2p3.fr/chamont/fast5x5
rm -rf boot.simd
