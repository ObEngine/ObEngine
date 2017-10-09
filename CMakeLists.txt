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

if(CMAKE_COMPILER_IS_GNUCC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fpermissive -O3")
endif()

add_subdirectory(extlibs/build/clipper)
add_subdirectory(extlibs/build/elzip)
add_subdirectory(extlibs/build/lua)
add_subdirectory(extlibs/build/TGUI)
add_subdirectory(extlibs/build/vili)
add_subdirectory(extlibs/build/dynamicLinker)

file(GLOB_RECURSE PG_OBE include/*.hpp)
file(GLOB_RECURSE HD_OBE src/*.cpp)

set_property(GLOBAL APPEND_STRING PROPERTY COMPILE_FLAGS -Wall)

find_package(SFML 2 REQUIRED graphics window system network audio)
add_subdirectory(extlibs/build/sfe)

IF (NOT DEFINED BUILD_TESTS)
    set(BUILD_TESTS OFF CACHE BOOL "Build ObEngine Tests ?")
ENDIF()

if(BUILD_TESTS)
    add_subdirectory(tests)
endif()

find_package(OpenGL REQUIRED)

include_directories(include/)
include_directories(extlibs/include/)

include_directories(${SFML_INCLUDE_DIR})
include_directories(${LUA53_INCLUDE_DIR})
include_directories(${OPENGL_INCLUDE_DIR})

add_executable(ObEngine ${PG_OBE} ${HD_OBE})

target_link_libraries(ObEngine clipper)
target_link_libraries(ObEngine elzip)
target_link_libraries(ObEngine lua)
target_link_libraries(ObEngine sfe)
target_link_libraries(ObEngine TGUI)
target_link_libraries(ObEngine vili)
target_link_libraries(ObEngine dynamicLinker)

if (UNIX)
    target_link_libraries(ObEngine ${CMAKE_DL_LIBS})
endif()

if(SFML_FOUND)
  target_link_libraries(ObEngine ${EXECUTABLE_NAME} ${SFML_LIBRARIES})
endif()

target_link_libraries(ObEngine ${OPENGL_LIBRARIES})

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

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 14)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_EXTENSIONS OFF)