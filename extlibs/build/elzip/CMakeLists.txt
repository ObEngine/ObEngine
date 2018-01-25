cmake_minimum_required(VERSION 3.6)
cmake_policy(SET CMP0015 NEW)

project(elzip)

add_subdirectory(minizip)

file(GLOB PG_LZIP 
    ../../include/elzip/unzipper.hpp 
    ../../include/elzip/zipper.hpp
    ../../include/elzip/elzip.hpp
)
file(GLOB HD_LZIP 
    src/unzipper.cpp
    src/zipper.cpp
    src/elzip.cpp
)

include_directories(../../include/minizip)

add_library(elzip ${PG_LZIP} ${HD_LZIP})
target_link_libraries(elzip minizip)

if (CMAKE_COMPILER_IS_GNUCXX)
    target_link_libraries(elzip stdc++fs)
endif()

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_EXTENSIONS OFF)

if (MSVC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++latest")
endif (MSVC)