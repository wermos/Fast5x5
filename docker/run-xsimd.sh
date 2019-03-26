#!/bin/bash
cd .. && docker run -it --rm  -v $PWD:/work -w /work gitlab-registry.in2p3.fr/codeursintensifs/fast5x5/xsimd:gsoc2019
