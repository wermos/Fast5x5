file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS *.cpp)

enable_testing()

add_executable(tests ${SOURCES})

target_link_libraries(tests PUBLIC gtest xsimd)
target_include_directories(test PUBLIC ../../libs/googletest/include)
target_include_directories(test PUBLIC ../../libs/xsimd/include)

add_test(tests tests)
