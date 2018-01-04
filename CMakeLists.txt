cmake_minimum_required(VERSION 3.5)
project (cpptest CXX)
add_subdirectory(example)

add_library(cpptest cppTest.cpp cppTest.h)

