cmake_minimum_required(VERSION 2.8)
cmake_policy(SET CMP0015 NEW)

project(ObEngineCore)

IF (NOT DEFINED _USE_CPP_NEW_FS)
    set(_USE_CPP_NEW_FS ON CACHE BOOL "Use C++17 Filesystem ?")
ENDIF()

if(_USE_CPP_NEW_FS)
    ADD_DEFINITIONS(-D_USE_CPP_NEW_FS)
endif()

if(CMAKE_COMPILER_IS_GNUCC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fpermissive -O3")
endif()

file(GLOB_RECURSE PG_OBE *.hpp)
file(GLOB_RECURSE HD_OBE *.cpp)

set_property(GLOBAL APPEND_STRING PROPERTY COMPILE_FLAGS -Wall)

include_directories(../../include/Core)
include_directories(../../extlibs/include/)

include_directories(${SFML_INCLUDE_DIR})
include_directories(${LUA53_INCLUDE_DIR})
include_directories(${OPENGL_INCLUDE_DIR})

add_library(ObEngineCore ${PG_OBE} ${HD_OBE})

target_link_libraries(ObEngineCore clipper)
target_link_libraries(ObEngineCore elzip)
target_link_libraries(ObEngineCore lua)
target_link_libraries(ObEngineCore sfe)
target_link_libraries(ObEngineCore vili)
target_link_libraries(ObEngineCore dynamicLinker)

if (UNIX)
    target_link_libraries(ObEngineCore ${CMAKE_DL_LIBS})
endif()

if(SFML_FOUND)
  target_link_libraries(ObEngineCore ${EXECUTABLE_NAME} ${SFML_LIBRARIES})
endif()

target_link_libraries(ObEngineCore ${OPENGL_LIBRARIES})

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