cmake_minimum_required(VERSION 2.8)
cmake_policy(SET CMP0015 NEW)

project(aube)

include_directories(../../include/aube/)
file(GLOB PG_AUBE ../../include/aube/*.hpp)
file(GLOB HD_AUBE src/*.cpp)

if(CMAKE_COMPILER_IS_GNUCC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fpermissive -O3")
endif()

add_library(aube ${PG_AUBE} ${HD_AUBE})

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 14)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_EXTENSIONS OFF)