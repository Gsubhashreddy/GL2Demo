cmake_minimum_required(VERSION 2.8)

project (coloring)

find_package(MPI)

# compilers to use (> 9.2)
set(CC /opt/homebrew/Cellar/gcc/12.2.0/bin/gcc-12)
set(CPP /opt/homebrew/Cellar/gcc/12.2.0/bin/g++-12)

SET(CMAKE_CXX_FLAGS "-O3 -std=c++11")

SET(CMAKE_C_COMPILER mpicc) 
SET(CMAKE_CXX_COMPILER mpicxx) 

# app targets
add_executable(round-mpi round-mpi.cpp)
