cmake_minimum_required(VERSION 3.21)
set(CMAKE_CXX_STANDARD 20)

enable_testing()
set(test_name subtract_with_carry_test)
add_executable(${test_name} main.cpp)
add_test(NAME ${test_name} COMMAND ${test_name})
target_include_directories(${test_name} SYSTEM PUBLIC)
