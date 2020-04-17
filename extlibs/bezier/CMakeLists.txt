project(bezier)

file(GLOB CATCH_HEADERS include/bezier/bezier.h)

add_library(bezier INTERFACE)

target_include_directories(bezier
    INTERFACE
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)