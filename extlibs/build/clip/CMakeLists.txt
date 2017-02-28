cmake_minimum_required(VERSION 2.8)
cmake_policy(SET CMP0015 NEW)

project(clip)

file(GLOB PG_CLIP ../../include/clip/*.h)
file(GLOB HD_CLIP ../../src/clip/*.cpp)

ADD_DEFINITIONS(-std=c++14)

if(CMAKE_COMPILER_IS_GNUCC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fpermissive -O3")
endif()

add_library(clip ${PG_CLIP} ${HD_CLIP})
