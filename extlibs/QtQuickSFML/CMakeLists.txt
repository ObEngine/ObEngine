cmake_minimum_required(VERSION 3.6)

project(QtQuickSFML)

file(GLOB QtQuickSFML_HEADERS include/QtQuickSFML/*.hpp)
file(GLOB QtQuickSFML_SOURCES src/*.cpp)

add_library(QtQuickSFML ${QtQuickSFML_HEADERS} ${QtQuickSFML_SOURCES})
target_link_libraries(QtQuickSFML sfml-graphics sfml-window)
target_link_libraries(QtQuickSFML Qt5::Core Qt5::Quick)

target_include_directories(QtQuickSFML
    PUBLIC 
        $<INSTALL_INTERFACE:include>    
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/QtQuickSFML>
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_EXTENSIONS OFF)

if (MSVC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++latest")
endif (MSVC)