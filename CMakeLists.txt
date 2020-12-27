cmake_minimum_required(VERSION 3.19)
project(armstrong C)

set(CMAKE_C_STANDARD 11)

add_executable(armstrong armstrong_numbers.c test/test_armstrong_numbers.c test/vendor/unity.c)