# FastMatrix
FastMatrix: A very efficient linear algebra library for extremely small matrices.

## Dependencies
 * libboost (>= 1.61)
 * bsimd

## Environment
Please make sure that your `$CPATH` (alternatively `$BOOST_SIMD_ROOT`) environment variable is correctly referencing Boost.SIMD include directory.

## Testing
You can test your configuration with `make test`. This must compile and run without error.

## Using the library
FastMatrix is a template-based header-only library. That means you don't need to compile anything before using it.

### Importing
There is only one header to import in order to use the library:
```c++
#include "../path/to/Fast-Matrix/fast_matrix.hpp"
```

### Creating a matrix
In order to create a squared matrix you need to create a object from the `BaseMatrix<Type, MatSize, MaxVecSize>` class
where `MatSize` is the matrix dimension and `MaxVecSize` the maximum vector size of type `Type` your hardware can support.

```c++
BaseMatrix<float, 5, 8> my_matrix;
```

By default your matrix will be initialized to zero.
If you want to initialize it to existing values you can pass an array to the constructor.
Values in the array are considered to be row-major.
```c++
double data[16] {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,160};
BaseMatrix<double, 4, 4> my_matrix(data);
```

### Getting the data back
You can dump the matrix data with the `dump_array()` method. The array is in row-major order.
```c++
double *data = my_matrix.dump_array();
```

### Printing values
`BaseMatrix` objects are printable with the `<<` operator:

```c++
std::cout << my_matrix << std::endl;
```
