project(lua)

file(GLOB LUA_HEADERS include/lua/*.h include/lua/*.hpp)
file(GLOB LUA_SOURCES src/*.c)

add_library(lua ${LUA_HEADERS} ${LUA_SOURCES})

target_include_directories(lua
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/lua>
)