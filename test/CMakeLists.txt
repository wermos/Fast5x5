
file(GLOB SRCS *.cpp)

enable_testing()
add_executable(unit_tests ${SRCS})
target_link_libraries(unit_tests libgtest)
#install(TARGETS unit_tests DESTINATION bin)
add_test(unit_tests unit_tests)
