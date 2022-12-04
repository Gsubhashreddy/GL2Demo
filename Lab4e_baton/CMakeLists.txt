cmake_minimum_required(VERSION 2.8)

project (coloring)

find_package(MPI)

SET(CMAKE_C_COMPILER mpicc) 
SET(CMAKE_CXX_COMPILER mpicxx) 

# app targets
add_executable(baton baton.cpp)
