project(entt)

file(GLOB ENTT_HEADERS include/entt/*.hpp)

add_library(entt INTERFACE)
add_library(entt::entt ALIAS entt)

target_include_directories(entt
    INTERFACE
        $<BUILD_INTERFACE:${lua_SOURCE_DIR}/include/entt>
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)