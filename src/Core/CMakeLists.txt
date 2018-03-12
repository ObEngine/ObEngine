cmake_minimum_required(VERSION 3.6)

project(ObEngineCore)

file(GLOB_RECURSE OBE_HEADERS ${ObEngine_SOURCE_DIR}/include/Core/*.hpp)
file(GLOB_RECURSE OBE_SOURCES ${ObEngine_SOURCE_DIR}/src/Core/*.cpp)

add_library(ObEngineCore ${OBE_HEADERS} ${OBE_SOURCES})

target_include_directories(ObEngineCore
  PUBLIC
    $<INSTALL_INTERFACE:${CMAKE_SOURCE_DIR}/include/Core>
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include/Core>
  PRIVATE
    $<BUILD_INTERFACE:${SFML_INCLUDE_DIR}>
    $<BUILD_INTERFACE:${OPENGL_INCLUDE_DIR}>
)

target_link_libraries(ObEngineCore elzip)
target_link_libraries(ObEngineCore lua)
target_link_libraries(ObEngineCore sfe)
target_link_libraries(ObEngineCore vili)
target_link_libraries(ObEngineCore dynamicLinker)
target_link_libraries(ObEngineCore spdlog)
target_link_libraries(ObEngineCore fmt)
target_link_libraries(ObEngineCore kaguya)

if (CMAKE_COMPILER_IS_GNUCXX)
    target_link_libraries(ObEngineCore stdc++fs)
endif()

if (UNIX)
    target_link_libraries(ObEngineCore ${CMAKE_DL_LIBS})
endif()

if (SFML_FOUND)
  target_link_libraries(ObEngineCore ${EXECUTABLE_NAME} ${SFML_LIBRARIES})
endif()

target_link_libraries(ObEngineCore ${OPENGL_LIBRARIES})

set(_inc_root_path ${ObEngine_SOURCE_DIR}/include/Core)
set(_src_root_path ${ObEngine_SOURCE_DIR}/src/Core)

foreach(_include IN ITEMS ${OBE_HEADERS})
    get_filename_component(_include_path "${_include}" PATH)
    file(RELATIVE_PATH _include_path_rel "${_inc_root_path}" "${_include_path}")
    string(REPLACE "/" "\\" _group_path "${_include_path_rel}")
    source_group("${_group_path}" FILES "${_include}")
endforeach()

foreach(_source IN ITEMS ${OBE_SOURCES})
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