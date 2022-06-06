cmake_minimum_required(VERSION 3.6)

project(vili-d8)

set(VILI_D8_HEADERS
    include/vld8/validator.hpp
    include/vld8/exceptions.hpp
)
set(VILI_D8_SOURCES
    src/validator.cpp
    src/validator.inl
    src/regex.inl
    src/pattern.inl
)

add_library(vili-d8 ${VILI_D8_HEADERS} ${VILI_D8_SOURCES})

target_link_libraries(vili-d8 vili)

target_include_directories(vili-d8
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_EXTENSIONS OFF)