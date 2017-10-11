cmake_minimum_required(VERSION 2.8)
cmake_policy(SET CMP0015 NEW)

project(ObEngineDev)

if(CMAKE_COMPILER_IS_GNUCC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fpermissive -O3")
endif()

file(GLOB_RECURSE HD_OBE_DEV *.cpp
                             ../Player/Modes/Game.cpp)

set_property(GLOBAL APPEND_STRING PROPERTY COMPILE_FLAGS -Wall)

include_directories(../../include/Core)
include_directories(../../include/Dev)
include_directories(../../include/Player)
include_directories(../../extlibs/include/)

include_directories(${SFML_INCLUDE_DIR})
include_directories(${LUA53_INCLUDE_DIR})
include_directories(${OPENGL_INCLUDE_DIR})

add_executable(ObEngineDev ${HD_OBE_DEV})

target_link_libraries(ObEngineDev ObEngineCore)

target_link_libraries(ObEngineDev lua)
target_link_libraries(ObEngineDev sfe)
target_link_libraries(ObEngineDev TGUI)
target_link_libraries(ObEngineDev vili)
target_link_libraries(ObEngineDev dynamicLinker)

if(SFML_FOUND)
  target_link_libraries(ObEngineDev ${EXECUTABLE_NAME} ${SFML_LIBRARIES})
endif()

target_link_libraries(ObEngineDev ${OPENGL_LIBRARIES})

if (UNIX)
    target_link_libraries(ObEngineDev ${CMAKE_DL_LIBS})
endif()

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 14)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_EXTENSIONS OFF)