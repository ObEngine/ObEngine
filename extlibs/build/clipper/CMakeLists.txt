cmake_minimum_required(VERSION 2.8)
cmake_policy(SET CMP0015 NEW)

project(clipper)

file(GLOB PG_CLIPPER ../../include/clipper/*.hpp)
file(GLOB HD_CLIPPER ../../src/clipper/*.cpp)

ADD_DEFINITIONS(-std=c++14)

if(CMAKE_COMPILER_IS_GNUCC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fpermissive -O3")
endif()

add_library(clipper ${PG_CLIPPER} ${HD_CLIPPER})
