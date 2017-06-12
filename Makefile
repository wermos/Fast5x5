CPATH := ${BOOST_SIMD_ROOT}
ifneq ($(CPATH),)
  CPATH := -I $(CPATH)
endif

CXX ?= g++
CXXFLAGS = -O3 -march=native

all:

test: bin/tests

bin/tests: tests.cpp fast_matrix.hpp
	$(CXX) $(CPATH) $(CXXFLAGS) $< -o $@
	$@

clean:
	rm -f bin/*
