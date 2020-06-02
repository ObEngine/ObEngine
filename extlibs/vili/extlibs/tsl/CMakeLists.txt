project(tsl)

file(GLOB_RECURSE TSL_HEADERS include/tsl/*.h include/tsl/*.hpp)

add_library(tsl INTERFACE)

target_include_directories(tsl
    INTERFACE
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/tsl>
)