# FastMatrix
FastMatrix: A very efficient linear algebra library for extremely small matrices.

## Dependencies
 * libboost (>= 1.61)
 * Boost.Simd

## Using the library
FastMatrix is a template-based header-only library.
That means the only requirement is to correctly add Boost.SIMD and Boost include directory at the list of directories used by your compiler.

### Importing
There is only one header to import in order to use the library:
```c++
#include "../path/to/Fast-Matrix/fast_matrix.hpp"
```

### Creating a matrix
In order to create a matrix you need to create a object from the `BaseMatrix<Type, NRows, NCols, MaxVecSize>` class
where `NRows` and `NCols` are the matrix dimensions and `MaxVecSize` the maximum vector size of type `Type` your hardware can support.

```c++
BaseMatrix<float, 2, 3, 8> my_matrix;
```

By default your matrix will be initialized to zero.
If you want to initialize it to existing values you can pass an array to the constructor.
Values in the array are considered to be row-major.
```c++
double data[16] {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,160};
BaseMatrix<double, 4, 4, 4> my_matrix(data);
```

### Getting the data back
You can dump the matrix data with the `dump_array()` method.
The returned value is an std::array in row-major order.
```c++
std::array<double, 4*4> data = my_matrix.dump_array();
```

### Printing values
`BaseMatrix` objects are printable with the `<<` operator:

```c++
std::cout << my_matrix << std::endl;
```

### Simple example
This is a simple example for matrix multiplication.

```c++
#include <iostream>

#include "../Fast-Matrix/fast_matrix.hpp"

int main (int argc, char **argv) {
    float left_data[6] = {
        1, 2, 3,
        4, 5, 6
    };
    float right_data[6] = {
        7, 8, 9,
        10, 11, 12
    };

    BaseMatrix<float, 2, 3, 8> a(left_data);
    BaseMatrix<float, 3, 2, 8> b(right_data);
    BaseMatrix<float, 2, 2, 8> c;

    matrix_mul_m_m(a, b, c); // The matrix product c = a*b

    std::cout << "A" << std::endl << a << std::endl;
    std::cout << "B" << std::endl << b << std::endl;
    std::cout << "C = A * B" << std::endl << c << std::endl;
}
```

## Testing
Testing functionalities of the library is available through a set of unit tests.
Prior running the tests you must build them with cmake.
Building them require to build Boost.SIMD first.

```bash
cd /path/to/Fast-Matrix/
mkdir build && cd build
export Boost_DIR=/path/to/boost/root # Only if you didn't install boost from your distribution
cmake -D CMAKE_PREFIX_PATH=path/to/boost.simd/build ..
make
```
Once the tests are built you can launch them from the test directory.
```bash
test/unit_tests
```
