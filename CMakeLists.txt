cmake_minimum_required(VERSION 2.8)
cmake_policy(SET CMP0015 NEW)

project(ObEngine)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/build-scripts/")

add_subdirectory(extlibs/build/clip)
add_subdirectory(extlibs/build/clipper)
add_subdirectory(extlibs/build/vili)

file(GLOB PG_OBE include/*.hpp)
file(GLOB HD_OBE src/*.cpp)

ADD_DEFINITIONS(-std=c++14)

set(CMAKE_MODULE_PATH build-scripts/ ${CMAKE_MODULE_PATH})
if(CMAKE_COMPILER_IS_GNUCC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fpermissive -O3")
endif()

set_property(GLOBAL APPEND_STRING PROPERTY COMPILE_FLAGS -Wall)

find_package(SFML 2 REQUIRED system window graphics network audio)
find_package(OpenGL REQUIRED)
find_package(Lua53 REQUIRED) 

add_executable(ObEngine ${PG_OBE} ${HD_OBE})

include_directories(include/)
include_directories(extlibs/include/)

include_directories(${LUA53_INCLUDE_DIR})
include_directories(${OPENGL_INCLUDE_DIR})

target_link_libraries(ObEngine clip)
target_link_libraries(ObEngine clipper)
target_link_libraries(ObEngine vili)

if(SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  target_link_libraries(ObEngine ${EXECUTABLE_NAME} ${SFML_LIBRARIES})
endif()
target_link_libraries(ObEngine ${LUA53_LIBRARIES})
target_link_libraries(ObEngine ${OPENGL_LIBRARIES})
