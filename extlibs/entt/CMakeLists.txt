project(entt)

file(GLOB_RECURSE ENTT_HEADERS include/entt/*.hpp include/entt/*.h)

add_library(entt INTERFACE)

target_include_directories(entt
    INTERFACE
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)