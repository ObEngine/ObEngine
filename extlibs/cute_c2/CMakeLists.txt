project(cute_c2)

file(GLOB CUTE_C2 include/cute/*.h)

add_library(cute_c2 INTERFACE)
add_library(cute::c2 ALIAS cute_c2)

target_include_directories(cute_c2
    INTERFACE
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)