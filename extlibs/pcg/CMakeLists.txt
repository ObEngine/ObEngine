project(pcg)

file(GLOB PCG_HEADERS include/pcg/*.hpp)

add_library(pcg INTERFACE)

target_include_directories(pcg
    INTERFACE
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)