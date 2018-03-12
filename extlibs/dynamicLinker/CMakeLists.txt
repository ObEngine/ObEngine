cmake_minimum_required(VERSION 3.6)

project(dynamicLinker)

file(GLOB DYLINK_HEADERS include/dynamicLinker/*.hpp)
file(GLOB DYLINK_SOURCES src/*.cpp)

add_library(dynamicLinker ${DYLINK_HEADERS} ${DYLINK_SOURCES})

target_include_directories(dynamicLinker
    PUBLIC 
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include/dynamicLinker
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_EXTENSIONS OFF)

if (MSVC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++latest")
endif (MSVC)