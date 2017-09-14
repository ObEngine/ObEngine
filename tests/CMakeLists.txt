cmake_minimum_required(VERSION 2.8)
cmake_policy(SET CMP0015 NEW)

project(ObEngineTests)

file(GLOB_RECURSE PG_OBT src/*.hpp)
file(GLOB_RECURSE HD_OBT 
    src/*.cpp
    ../src/*.cpp
)

FOREACH(item ${HD_OBT})
  IF(${item} MATCHES "ObEngine.cpp")
    LIST(REMOVE_ITEM HD_OBT ${item})
  ENDIF(${item} MATCHES "ObEngine.cpp")
ENDFOREACH(item)

set_property(GLOBAL APPEND_STRING PROPERTY COMPILE_FLAGS -Wall)

find_package(OpenGL REQUIRED)

include_directories(../include/)
include_directories(../extlibs/include/)

include_directories(${SFML_INCLUDE_DIR})
include_directories(${LUA53_INCLUDE_DIR})
include_directories(${OPENGL_INCLUDE_DIR})

add_executable(ObEngineTests ${PG_OBT} ${HD_OBT})

target_link_libraries(ObEngineTests clipper)
target_link_libraries(ObEngineTests elzip)
target_link_libraries(ObEngineTests lua)
target_link_libraries(ObEngineTests sfe)
target_link_libraries(ObEngineTests TGUI)
target_link_libraries(ObEngineTests vili)
target_link_libraries(ObEngineTests dynamicLinker)

if (UNIX)
    target_link_libraries(ObEngineTests ${CMAKE_DL_LIBS})
endif()

if(SFML_FOUND)
  target_link_libraries(ObEngineTests ${EXECUTABLE_NAME} ${SFML_LIBRARIES})
endif()

target_link_libraries(ObEngineTests ${OPENGL_LIBRARIES})

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 14)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_EXTENSIONS OFF)