project(fswrapper)

file(GLOB FSWRAPPER_HEADERS include/fswrapper/fswrapper.hpp)

add_library(fswrapper INTERFACE)

target_include_directories(fswrapper 
    INTERFACE 
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)