cmake_minimum_required(VERSION 2.8)
cmake_policy(SET CMP0015 NEW)

project(aube)

include_directories(../../include/aube/)
file(GLOB PG_AUBE ../../include/aube/*.hpp)
file(GLOB HD_AUBE src/*.cpp)

ADD_DEFINITIONS(-std=c++14)

if(CMAKE_COMPILER_IS_GNUCC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fpermissive -O3")
endif()

add_library(aube ${PG_AUBE} ${HD_AUBE})
