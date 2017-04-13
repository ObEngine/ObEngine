cmake_minimum_required(VERSION 2.8)
cmake_policy(SET CMP0015 NEW)

project(vili)

include_directories(../../include/)
include_directories(../../include/vili/)
file(GLOB PG_VILI ../../include/vili/*.hpp)
file(GLOB HD_VILI src/*.cpp)

ADD_DEFINITIONS(-std=c++14)

if(CMAKE_COMPILER_IS_GNUCC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fpermissive -O3")
else()
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
endif()

add_library(vili ${PG_VILI} ${HD_VILI})
