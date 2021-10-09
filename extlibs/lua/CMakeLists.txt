project(lua LANGUAGES CXX)

set(LUA_SOURCES
    "src/ldblib.c"
    "src/ldebug.c"
    "src/ldo.c"
    "src/ldump.c"
    "src/lfunc.c"
    "src/lgc.c"
    "src/linit.c"
    "src/liolib.c"
    "src/lopcodes.c"
    "src/llex.c"
    "src/lmathlib.c"
    "src/lmem.c"
    "src/loadlib.c"
    "src/lobject.c"
    "src/loslib.c"
    "src/lparser.c"
    "src/lstate.c"
    "src/lstring.c"
    "src/lstrlib.c"
    "src/ltable.c"
    "src/ltablib.c"
    "src/ltm.c"
    "src/lundump.c"
    "src/lutf8lib.c"
    "src/lvm.c"
    "src/lzio.c"
    "src/lapi.c"
    "src/lauxlib.c"
    "src/lbaselib.c"
    "src/lcode.c"
    "src/lcorolib.c"
    "src/lctype.c"
)

set_source_files_properties(${LUA_HEADERS} PROPERTIES LANGUAGE CXX)
set_source_files_properties(${LUA_SOURCES} PROPERTIES LANGUAGE CXX)

add_library(lua ${LUA_SOURCES})

set_target_properties(lua PROPERTIES LINKER_LANGUAGE CXX)

if (MSVC)
    target_compile_options(lua PRIVATE /TP /Zc:__cplusplus)
endif ()

target_include_directories(lua
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/lua>
)