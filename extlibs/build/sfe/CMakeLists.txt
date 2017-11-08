cmake_minimum_required(VERSION 3.6)
cmake_policy(SET CMP0015 NEW)

project(sfe)

include_directories(../../include/sfe/)
include_directories(${SFML_INCLUDE_DIR})

file(GLOB PG_SFE ../../include/sfe/*.hpp)
file(GLOB HD_SFE src/*.cpp)

add_library(sfe ${PG_SFE} ${HD_SFE})

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 14)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_EXTENSIONS OFF)