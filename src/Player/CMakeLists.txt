cmake_minimum_required(VERSION 2.8)
cmake_policy(SET CMP0015 NEW)

project(ObEnginePlayer)

if(CMAKE_COMPILER_IS_GNUCC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fpermissive -O3")
endif()

file(GLOB_RECURSE PG_OBE_PLAY "${ObEngine_SOURCE_DIR}/include/Player/*.hpp")
file(GLOB_RECURSE HD_OBE_PLAY "${ObEngine_SOURCE_DIR}/src/Player/*.cpp")

set_property(GLOBAL APPEND_STRING PROPERTY COMPILE_FLAGS -Wall)

include_directories(../../include/Core)
include_directories(../../include/Player)
include_directories(../../extlibs/include/)

include_directories(${SFML_INCLUDE_DIR})
include_directories(${LUA53_INCLUDE_DIR})
include_directories(${OPENGL_INCLUDE_DIR})

add_executable(ObEnginePlayer ${HD_OBE_PLAY} ${PG_OBE_PLAY})

target_link_libraries(ObEnginePlayer ObEngineCore)

target_link_libraries(ObEnginePlayer lua)
target_link_libraries(ObEnginePlayer sfe)
target_link_libraries(ObEnginePlayer vili)
target_link_libraries(ObEnginePlayer dynamicLinker)

if(SFML_FOUND)
  target_link_libraries(ObEnginePlayer ${EXECUTABLE_NAME} ${SFML_LIBRARIES})
endif()

target_link_libraries(ObEnginePlayer ${OPENGL_LIBRARIES})

if (UNIX)
    target_link_libraries(ObEnginePlayer ${CMAKE_DL_LIBS})
endif()

set(_inc_root_path "${ObEngine_SOURCE_DIR}/include/Player")
set(_src_root_path "${ObEngine_SOURCE_DIR}/src/Player")

foreach(_include IN ITEMS ${PG_OBE_PLAY})
    get_filename_component(_include_path "${_include}" PATH)
    file(RELATIVE_PATH _include_path_rel "${_inc_root_path}" "${_include_path}")
    string(REPLACE "/" "\\" _group_path "${_include_path_rel}")
    source_group("${_group_path}" FILES "${_include}")
endforeach()

foreach(_source IN ITEMS ${HD_OBE_PLAY})
    get_filename_component(_source_path "${_source}" PATH)
    file(RELATIVE_PATH _source_path_rel "${_src_root_path}" "${_source_path}")
    string(REPLACE "/" "\\" _group_path "${_source_path_rel}")
    source_group("${_group_path}" FILES "${_source}")
endforeach()

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 14)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_EXTENSIONS OFF)