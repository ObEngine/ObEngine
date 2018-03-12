cmake_minimum_required(VERSION 3.6)

project(TGUI)

file(GLOB_RECURSE TGUI_HEADERS include/TGUI/*.hpp include/TGUI/*.inl)
file(GLOB_RECURSE TGUI_SOURCES src/*.cpp)

add_library(TGUI ${TGUI_HEADERS} ${TGUI_SOURCES})

target_include_directories(TGUI
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${SFML_INCLUDE_DIR}
)

target_compile_definitions(TGUI PRIVATE TGUI_STATIC)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_EXTENSIONS OFF)

if (MSVC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++latest")
endif (MSVC)