cmake_minimum_required(VERSION 2.8)
cmake_policy(SET CMP0015 NEW)

project(elzip)

add_subdirectory(minizip)

file(GLOB PG_LZIP src/*.hpp)
file(GLOB HD_LZIP src/*.cpp)

include_directories(../../include/minizip)

add_library(elzip ${PG_LZIP} ${HD_LZIP})
target_link_libraries(elzip minizip)