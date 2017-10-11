cmake_minimum_required(VERSION 2.8)
cmake_policy(SET CMP0015 NEW)

project(ObEngine)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/extlibs/find/")

IF (NOT DEFINED _USE_CPP_NEW_FS)
    set(_USE_CPP_NEW_FS ON CACHE BOOL "Use C++17 Filesystem ?")
ENDIF()

if(_USE_CPP_NEW_FS)
    ADD_DEFINITIONS(-D_USE_CPP_NEW_FS)
endif()

add_subdirectory(extlibs/build/clipper)
add_subdirectory(extlibs/build/elzip)
add_subdirectory(extlibs/build/lua)
add_subdirectory(extlibs/build/TGUI)
add_subdirectory(extlibs/build/vili)
add_subdirectory(extlibs/build/dynamicLinker)

find_package(SFML 2 REQUIRED graphics window system network audio)
find_package(OpenGL REQUIRED)
add_subdirectory(extlibs/build/sfe)

add_subdirectory(src/Core)

IF (NOT DEFINED BUILD_PLAYER)
    set(BUILD_PLAYER ON CACHE BOOL "Build ObEngine Player ?")
ENDIF()

if(BUILD_PLAYER)
    add_subdirectory(src/Player)
endif()

IF (NOT DEFINED BUILD_DEV)
    set(BUILD_DEV ON CACHE BOOL "Build ObEngine Dev ?")
ENDIF()

if(BUILD_DEV)
    add_subdirectory(src/Dev)
endif()

IF (NOT DEFINED BUILD_TESTS)
    set(BUILD_TESTS OFF CACHE BOOL "Build ObEngine Tests ?")
ENDIF()

if(BUILD_TESTS)
    add_subdirectory(tests)
endif()

set(_inc_root_path "${ObEngine_SOURCE_DIR}/include/")
file(
    GLOB_RECURSE _inc_list 
    LIST_DIRECTORIES false
    "${_inc_root_path}/*.hpp"
)
set(_src_root_path "${ObEngine_SOURCE_DIR}/src/")
file(
    GLOB_RECURSE _src_list 
    LIST_DIRECTORIES false
    "${_src_root_path}/*.cpp"
)

foreach(_include IN ITEMS ${_inc_list})
    get_filename_component(_include_path "${_include}" PATH)
    file(RELATIVE_PATH _include_path_rel "${_inc_root_path}" "${_include_path}")
    string(REPLACE "/" "\\" _group_path "${_include_path_rel}")
    source_group("${_group_path}" FILES "${_include}")
endforeach()

foreach(_source IN ITEMS ${_src_list})
    get_filename_component(_source_path "${_source}" PATH)
    file(RELATIVE_PATH _source_path_rel "${_src_root_path}" "${_source_path}")
    string(REPLACE "/" "\\" _group_path "${_source_path_rel}")
    source_group("${_group_path}" FILES "${_source}")
endforeach()