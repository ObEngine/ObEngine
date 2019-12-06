project(TGUI VERSION 0.8.6)

file(GLOB_RECURSE TGUI_HEADERS include/TGUI/*.hpp include/TGUI/*.inl)
file(GLOB_RECURSE TGUI_SOURCES src/*.cpp)

add_library(tgui ${TGUI_SOURCES})
target_link_libraries(tgui sfml-graphics)

target_include_directories(tgui
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_compile_definitions(tgui PRIVATE TGUI_STATIC)
set(TGUI_CXX_STANDARD 17)

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/include/TGUI/Config.hpp.in 
    ${CMAKE_CURRENT_SOURCE_DIR}/include/TGUI/Config.hpp @ONLY)

set_property(TARGET tgui PROPERTY CXX_STANDARD 17)
set_property(TARGET tgui PROPERTY CXX_STANDARD_REQUIRED ON)
set_property(TARGET tgui PROPERTY CXX_EXTENSIONS OFF)