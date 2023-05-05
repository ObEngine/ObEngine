project(brynet)

add_library(brynet INTERFACE)

target_include_directories(brynet
    INTERFACE
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)