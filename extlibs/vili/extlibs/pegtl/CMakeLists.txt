project(pegtl)

file(GLOB_RECURSE PEGTL_HEADERS include/tao/*.hpp)

add_library(pegtl INTERFACE)

target_include_directories(pegtl
    INTERFACE
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)