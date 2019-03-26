
# This image is used to pack the needed externals for Fast5x5
FROM ubuntu:bionic

# => g++ 7.3.0
# => R 3.4.4
# => Eigen 3.3.4-4

# Ensure use of bash
SHELL ["/bin/bash","-c"]

# So to avoid debconf interactive questions
RUN echo 'debconf debconf/frontend select Noninteractive' | debconf-set-selections
ARG DEBIAN_FRONTEND=noninteractive

# Installations apt-get
RUN apt-get update \
&& apt-get install -y apt-utils \
&& apt-get install -y time \
&& apt-get install -y bc \
&& apt-get install -y vim \
&& apt-get install -y wget \
&& apt-get install -y x11-apps \
&& apt-get install -y xemacs21 \
&& apt-get install -y cmake \
&& apt-get install -y git \
&& apt-get install -y r-base \
&& apt-get install -y libeigen3-dev \
&& rm -rf /var/lib/apt/lists/*

# Kokkos
ENV KOKKOS_PATH /opt/kokkos
ENV KOKKOS_VERSION 2.7.24
RUN git clone https://github.com/kokkos/kokkos.git -b ${KOKKOS_VERSION} ${KOKKOS_PATH} && \
    ${KOKKOS_PATH}/generate_makefile.bash --kokkos-path=${KOKKOS_PATH} --prefix=${KOKKOS_PATH}
