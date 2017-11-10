cmake_minimum_required(VERSION 3.6)
cmake_policy(SET CMP0015 NEW)

project(dynamicLinker)

file(GLOB PG_DYLINK ../../include/dynamicLinker/*.hpp)
file(GLOB HD_DYLINK src/*.cpp)

include_directories(../../include/dynamicLinker/)

add_library(dynamicLinker ${PG_DYLINK} ${HD_DYLINK})

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_EXTENSIONS OFF)

if (MSVC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++latest")
endif (MSVC)