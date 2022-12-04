cmake_minimum_required(VERSION 2.8)

project (coloring)

find_package(MPI)

SET(CMAKE_C_COMPILER mpicc) 
SET(CMAKE_CXX_COMPILER mpicxx) 

# app targets
add_executable(color src/color.cpp)
#target_link_libraries(color mpi)
