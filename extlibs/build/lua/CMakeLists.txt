cmake_minimum_required(VERSION 2.8)
cmake_policy(SET CMP0015 NEW)

project(lua)

file(GLOB PG_LUA ../../include/lua/*.h)
file(GLOB HD_LUA src/*.c)

if(CMAKE_COMPILER_IS_GNUCC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fpermissive -O3")
else()
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
endif()

add_library(lua ${PG_LUA} ${HD_LUA})
