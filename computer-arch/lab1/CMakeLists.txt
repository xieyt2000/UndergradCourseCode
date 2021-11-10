cmake_minimum_required(VERSION 3.17)
project(lab1)

set(CMAKE_CXX_STANDARD 14)
# disable the following line when calculating matrix multiplication
set(CMAKE_CXX_FLAGS "-D_GNU_SOURCE -O3 ${CMAKE_CXX_FLAGS}")

add_executable(lab1 main.cpp measure.cpp measure.h)