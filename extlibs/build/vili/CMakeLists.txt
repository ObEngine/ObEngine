cmake_minimum_required(VERSION 2.8)
cmake_policy(SET CMP0015 NEW)

project(vili)

include_directories(../../include/vili/)
include_directories(../../include/vili/vili/)

file(GLOB PG_VILI ../../include/vili/*.hpp)
file(GLOB PG_VILI 
  ../../include/vili/*.hpp
  ../../include/vili/vili/*.hpp
)
file(GLOB HD_VILI 
  src/*.cpp
  src/vili/*.cpp
  src/vili/*.inl
)

if(CMAKE_COMPILER_IS_GNUCC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fpermissive -O3")
endif()

add_library(vili ${PG_VILI} ${HD_VILI})

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 14)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_EXTENSIONS OFF)