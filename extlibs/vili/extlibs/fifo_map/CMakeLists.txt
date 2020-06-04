project(fifo_map)

file(GLOB_RECURSE FIFO_HEADERS include/nlohmann/*.hpp)

add_library(fifo_map INTERFACE)

target_include_directories(fifo_map
    INTERFACE
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/nlohmann>
)