cmake_minimum_required(VERSION 3.6)

project(android-app-glue)

file(GLOB ANDROIDAG_HEADERS include/*.h)
file(GLOB ANDROIDAG_SOURCES src/*.c)

add_library(android-app-glue STATIC ${ANDROIDAG_HEADERS} ${ANDROIDAG_SOURCES})

target_include_directories(android-app-glue
    PUBLIC 
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include/
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)