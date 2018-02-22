
# This image is used to pack the needed externals for Fast5x5
FROM gcc:7.2

# Ensure use of bash
SHELL ["/bin/bash","-c"]

# So to avoid debconf interactive questions
#RUN echo 'debconf debconf/frontend select Noninteractive' | debconf-set-selections
ARG DEBIAN_FRONTEND=noninteractive

RUN apt-get update \
&& apt-get install -y apt-utils \
&& apt-get install -y vim \
&& apt-get install -y wget \
&& apt-get install -y x11-apps \
&& apt-get install -y xemacs21 \
&& apt-get install -y cmake \
&& rm -rf /var/lib/apt/lists/*

# boost
RUN export BOOST_VERSION="1.62.0" && export BOOST_VERSION_=${BOOST_VERSION//./_} && \
    wget -O boost-${BOOST_VERSION_}.tar.gz http://downloads.sourceforge.net/project/boost/boost/${BOOST_VERSION}/boost_${BOOST_VERSION_}.tar.gz && \
    tar xf boost-${BOOST_VERSION_}.tar.gz && \
    cd boost_${BOOST_VERSION_}/ && \
    ./bootstrap.sh --prefix=/opt/boost/ --with-libraries=program_options,test && \
    ./b2 install && \
    cd .. && rm boost-${BOOST_VERSION_}.tar.gz && rm -r boost_${BOOST_VERSION_}
ENV BOOST_ROOT /opt/boost

# bSIMD
RUN git clone https://github.com/NumScale/boost.simd.git -b master /opt/boost.simd
ENV BOOST_SIMD_ROOT /opt/boost.simd

# Use of BOOST and BOOST.SIMD
ENV CPATH ${BOOST_SIMD_ROOT}/include:${BOOST_ROOT}/include

# Eigen, for test & benchmarking
RUN export EIGEN_VERSION="3.2.10" && \
    wget http://bitbucket.org/eigen/eigen/get/${EIGEN_VERSION}.tar.gz && \
    tar xf ${EIGEN_VERSION}.tar.gz && \
    mkdir -p /opt/ && \
    mv eigen-eigen-*/ /opt/eigen/ && \
    rm ${EIGEN_VERSION}.tar.gz

# Google Test, for test & benchmarking
RUN git clone https://github.com/google/googletest.git -b release-1.8.0 /opt/googletest
ENV GTEST_ROOT /opt/googletest/googletest



