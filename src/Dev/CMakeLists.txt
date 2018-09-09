cmake_minimum_required(VERSION 3.6)

project(ObEngineDev)

file(GLOB_RECURSE OBEDEV_HEADERS 
  ${ObEngine_SOURCE_DIR}/include/Dev/*.hpp
  ${ObEngine_SOURCE_DIR}/include/Player/Modes/Game.hpp)
file(GLOB_RECURSE OBEDEV_SOURCES 
  ${ObEngine_SOURCE_DIR}/src/Dev/*.cpp
  ${ObEngine_SOURCE_DIR}/src/Player/Modes/Game.cpp)

add_executable(ObEngineDev ${OBEDEV_HEADERS} ${OBEDEV_SOURCES})

target_include_directories(ObEngineDev
  PRIVATE
    $<BUILD_INTERFACE:${ObEngine_SOURCE_DIR}/include/Player>
    $<BUILD_INTERFACE:${ObEngine_SOURCE_DIR}/include/Dev>
)

target_link_libraries(ObEngineDev ObEngineCore)

target_link_libraries(ObEngineDev fmt)
target_link_libraries(ObEngineDev lua)
target_link_libraries(ObEngineDev sfe)
target_link_libraries(ObEngineDev TGUI)
target_link_libraries(ObEngineDev vili)
target_link_libraries(ObEngineDev dynamicLinker)

if(SFML_FOUND)
  target_link_libraries(ObEngineDev sfml-window)
endif()

if (UNIX)
    target_link_libraries(ObEngineDev ${CMAKE_DL_LIBS})
endif()

set(_inc_root_path "${ObEngine_SOURCE_DIR}/include/Dev")
set(_src_root_path "${ObEngine_SOURCE_DIR}/src/Dev")

foreach(_include IN ITEMS ${OBEDEV_HEADERS})
    get_filename_component(_include_path "${_include}" PATH)
    file(RELATIVE_PATH _include_path_rel "${_inc_root_path}" "${_include_path}")
    string(REPLACE "/" "\\" _group_path "${_include_path_rel}")
    source_group("${_group_path}" FILES "${_include}")
endforeach()

foreach(_source IN ITEMS ${OBEDEV_SOURCES})
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