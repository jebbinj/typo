cmake_minimum_required(VERSION 3.17)
project(typo)

set(CMAKE_CXX_STANDARD 17)

add_executable(typo src/main.cpp src/function.h src/function.cpp src/testfunc.cpp src/testfunc.h)