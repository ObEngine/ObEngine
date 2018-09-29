project(TGUI)

file(GLOB_RECURSE TGUI_HEADERS include/TGUI/*.hpp include/TGUI/*.inl)
file(GLOB_RECURSE TGUI_SOURCES src/*.cpp)

add_library(TGUI ${TGUI_HEADERS} ${TGUI_SOURCES})
target_link_libraries(TGUI sfml-graphics)

target_include_directories(TGUI
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_compile_definitions(TGUI PRIVATE TGUI_STATIC)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 14)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_EXTENSIONS OFF)