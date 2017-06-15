GTEST_DIR := /usr/src/googletest/googletest

CPATH := ${BOOST_SIMD_ROOT}
ifneq ($(CPATH),)
  CPATH := -I $(CPATH)
endif

CXX ?= g++
CXXFLAGS = -O3 -march=native

all:

lib/gtest-all.o: $(GTEST_DIR)/src/gtest-all.cc
	g++ -isystem $(GTEST_DIR)/include -I $(GTEST_DIR) -pthread -c $< -o $@

obj/unit_%.o: tests/unit_%.cpp fast_matrix.hpp
	$(CXX) $(CPATH) $(CXXFLAGS) -isystem $(GTEST_DIR)/include -pthread $< -c -o $@

test: bin/tests

bin/tests: tests/run_all.cpp $(patsubst tests/unit_%.cpp,obj/unit_%.o,$(wildcard tests/unit_*.cpp)) fast_matrix.hpp lib/gtest-all.o
	$(CXX) $(CPATH) $(CXXFLAGS) -isystem $(GTEST_DIR)/include -pthread $^ -o $@
	$@

clean:
	rm -f bin/*
	rm -f lib/*
	rm -f obj/*
