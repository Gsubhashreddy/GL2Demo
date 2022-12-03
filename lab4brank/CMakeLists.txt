cmake_minimum_required(VERSION 2.8)

project (rank)

# compilers to use (> 9.2)
#set(CC /opt/homebrew/Cellar/gcc/12.2.0/bin/gcc-12)
#set(CPP  /opt/homebrew/Cellar/gcc/12.2.0/bin/g++-12)

SET(CMAKE_CXX_FLAGS "-O3 -std=c++11")

SET(CMAKE_C_COMPILER mpicc) 
SET(CMAKE_CXX_COMPILER mpicxx) 

# no boost libraries are used, yet
#find_package(Boost 1.72 REQUIRED)
#include_directories(${Boost_INCLUDE_DIRS})
#include_directories(${CMAKE_SOURCE_DIR})
#set(Boost_USE_STATIC_LIBS ON)
#set(Boost_USE_MULTITHREADED ON)
#set(Boost_USE_STATIC_RUNTIME ON)
#set(BOOST_ROOT "/usr/local/gcc/boost_1_72_0")

# app targets
add_executable(rank src/rank.cpp)

target_compile_features(rank
   PRIVATE 
      cxx_std_17
   )

