project(sol3)

file(GLOB SOL_HEADERS include/sol/*.hpp)

add_library(sol3 INTERFACE)

target_link_libraries(sol3 INTERFACE lua)

target_include_directories(sol3
    INTERFACE
        $<BUILD_INTERFACE:${lua_SOURCE_DIR}/include/lua>
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)
target_compile_definitions(sol3 INTERFACE SOL_ALL_SAFETIES_ON)