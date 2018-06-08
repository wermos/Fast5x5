
file(GLOB SRCS *.cpp)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native")

enable_testing()
add_executable(unit_tests ${SRCS})
target_link_libraries(unit_tests PRIVATE libgtest xsimd)
#install(TARGETS unit_tests DESTINATION bin)
add_test(unit_tests unit_tests)
