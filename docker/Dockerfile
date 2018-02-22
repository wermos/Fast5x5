FROM gitlab-registry.in2p3.fr/maitresnageurs/piscineji:calculbsimd

# Ensure use of bash
SHELL ["/bin/bash","-c"]

# Eigen
RUN export EIGEN_VERSION="3.2.10" && \
    wget http://bitbucket.org/eigen/eigen/get/${EIGEN_VERSION}.tar.gz && \
    tar xf ${EIGEN_VERSION}.tar.gz && \
    mkdir -p /opt/ && \
    mv eigen-eigen-*/ /opt/eigen/ && \
    rm ${EIGEN_VERSION}.tar.gz

# Google Test
RUN git clone https://github.com/google/googletest.git -b release-1.8.0 /opt/googletest
ENV GTEST_ROOT /opt/googletest/googletest

# Use of BOOST and BOOST.SIMD
ENV CPATH ${BOOST_SIMD_ROOT}/include:${BOOST_ROOT}/include

