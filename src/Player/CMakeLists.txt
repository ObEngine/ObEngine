cmake_minimum_required(VERSION 3.6)

project(ObEnginePlayer)

file(GLOB_RECURSE OBEPLAYER_HEADERS "${ObEngine_SOURCE_DIR}/include/Player/*.hpp")
file(GLOB_RECURSE OBEPLAYER_SOURCES "${ObEngine_SOURCE_DIR}/src/Player/*.cpp")

add_executable(ObEnginePlayer ${OBEPLAYER_HEADERS} ${OBEPLAYER_SOURCES})

target_include_directories(ObEnginePlayer
  PRIVATE
    $<BUILD_INTERFACE:${ObEngine_SOURCE_DIR}/include/Player>
    $<BUILD_INTERFACE:${OPENGL_INCLUDE_DIR}>
)

target_link_libraries(ObEnginePlayer ObEngineCore)

target_link_libraries(ObEnginePlayer lua)
target_link_libraries(ObEnginePlayer sfe)
target_link_libraries(ObEnginePlayer vili)
target_link_libraries(ObEnginePlayer dynamicLinker)

if(SFML_FOUND)
  target_link_libraries(ObEnginePlayer sfml-window)
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

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_EXTENSIONS OFF)

if (MSVC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++latest")
endif (MSVC)