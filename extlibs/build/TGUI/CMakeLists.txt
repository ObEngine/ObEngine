cmake_minimum_required(VERSION 3.6)
cmake_policy(SET CMP0015 NEW)

project(TGUI)

file(GLOB_RECURSE PG_TGUI 
    ../../include/TGUI/*.hpp
    ../../include/TGUI/*.inl
)
file(GLOB_RECURSE HD_TGUI 
    src/*.cpp
)
include_directories(../../include/)
include_directories(${SFML_INCLUDE_DIR})

message("TGUI found SFML : ${SFML_INCLUDE_DIR}")

if(CMAKE_COMPILER_IS_GNUCC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fpermissive -O3")
endif()

add_library(TGUI ${PG_TGUI} ${HD_TGUI})

ADD_DEFINITIONS(-DTGUI_STATIC)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_EXTENSIONS OFF)

if (MSVC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++latest")
endif (MSVC)