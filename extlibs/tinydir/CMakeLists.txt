project(tinydir)

file(GLOB TINYDIR_HEADERS include/tinydir/tinydir.h)

add_library(tinydir INTERFACE)

target_include_directories(tinydir 
    INTERFACE 
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)