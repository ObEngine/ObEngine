cmake_minimum_required(VERSION 3.6)
cmake_policy(SET CMP0015 NEW)

project(clipper)

file(GLOB PG_CLIPPER ../../include/clipper/*.hpp)
file(GLOB HD_CLIPPER src/*.cpp)

if(CMAKE_COMPILER_IS_GNUCC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fpermissive -O3")
endif()

add_library(clipper ${PG_CLIPPER} ${HD_CLIPPER})

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_EXTENSIONS OFF)

if (MSVC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++latest")
endif (MSVC)