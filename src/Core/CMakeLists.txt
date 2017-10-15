cmake_minimum_required(VERSION 2.8)
cmake_policy(SET CMP0015 NEW)

project(ObEngineCore)

if(CMAKE_COMPILER_IS_GNUCC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fpermissive -O3")
endif()

file(GLOB_RECURSE PG_OBE "${ObEngine_SOURCE_DIR}/include/Core/*.hpp")
file(GLOB_RECURSE HD_OBE "${ObEngine_SOURCE_DIR}/src/Core/*.cpp")

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

IF(CMAKE_COMPILER_IS_GNUCXX AND _USE_CPP_NEW_FS)
  target_link_libraries(ObEngineCore stdc++fs)
ENDIF()

if (UNIX)
    target_link_libraries(ObEngineCore ${CMAKE_DL_LIBS})
endif()

if(SFML_FOUND)
  target_link_libraries(ObEngineCore ${EXECUTABLE_NAME} ${SFML_LIBRARIES})
endif()

target_link_libraries(ObEngineCore ${OPENGL_LIBRARIES})

set(_inc_root_path "${ObEngine_SOURCE_DIR}/include/Core")
set(_src_root_path "${ObEngine_SOURCE_DIR}/src/Core")

foreach(_include IN ITEMS ${PG_OBE})
    get_filename_component(_include_path "${_include}" PATH)
    file(RELATIVE_PATH _include_path_rel "${_inc_root_path}" "${_include_path}")
    string(REPLACE "/" "\\" _group_path "${_include_path_rel}")
    source_group("${_group_path}" FILES "${_include}")
endforeach()

foreach(_source IN ITEMS ${HD_OBE})
    get_filename_component(_source_path "${_source}" PATH)
    file(RELATIVE_PATH _source_path_rel "${_src_root_path}" "${_source_path}")
    string(REPLACE "/" "\\" _group_path "${_source_path_rel}")
    source_group("${_group_path}" FILES "${_source}")
endforeach()

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 14)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_EXTENSIONS OFF)