cmake_minimum_required(VERSION 3.6)

project(elzip)

file(GLOB LZIP_HEADERS include/elzip/*.hpp)
file(GLOB LZIP_SOURCES src/*.cpp)

add_library(elzip ${LZIP_HEADERS} ${LZIP_SOURCES})
target_link_libraries(elzip minizip)

if (CMAKE_COMPILER_IS_GNUCXX)
    target_link_libraries(elzip stdc++fs)
endif()

target_include_directories(elzip
    PUBLIC 
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/elzip>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_EXTENSIONS OFF)

if (MSVC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++latest")
endif (MSVC)