cmake_minimum_required(VERSION 3.6)

project(vili-msgpack)

set(VILI_MSGPACK_HEADERS
    include/vili-msgpack/msgpack.hpp
    include/vili-msgpack/exceptions.hpp
)
set(VILI_MSGPACK_SOURCES
    src/msgpack.cpp
)

add_library(vili-msgpack ${VILI_MSGPACK_HEADERS} ${VILI_MSGPACK_SOURCES})

target_link_libraries(vili-msgpack vili)

target_include_directories(vili-msgpack
    PUBLIC
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_EXTENSIONS OFF)