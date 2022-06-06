project(magic_enum)

file(GLOB MAGIC_ENUM_HEADERS include/magic_enum/magic_enum.hpp)

add_library(magic_enum INTERFACE)

target_include_directories(magic_enum
    INTERFACE
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)