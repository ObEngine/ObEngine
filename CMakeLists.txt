cmake_minimum_required(VERSION 2.8)
cmake_policy(SET CMP0015 NEW)

project(ObEngine)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/build-scripts/")

IF (NOT DEFINED _USE_CPP_NEW_FS)
    set(_USE_CPP_NEW_FS ON CACHE BOOL "Use C++17 Filesystem ?")
ENDIF()
ADD_DEFINITIONS(-D_USE_CPP_NEW_FS=${_MYDEFINE})


add_subdirectory(extlibs/build/clip)
add_subdirectory(extlibs/build/clipper)
add_subdirectory(extlibs/build/vili)
add_subdirectory(extlibs/build/elzip)
add_subdirectory(extlibs/build/lua)
add_subdirectory(extlibs/build/tgui)

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

add_executable(ObEngine ${PG_OBE} ${HD_OBE})

include_directories(include/)
include_directories(extlibs/include/)

include_directories(${LUA53_INCLUDE_DIR})
include_directories(${OPENGL_INCLUDE_DIR})

target_link_libraries(ObEngine clip)
target_link_libraries(ObEngine clipper)
target_link_libraries(ObEngine vili)
target_link_libraries(ObEngine elzip)
target_link_libraries(ObEngine lua)
target_link_libraries(ObEngine tgui)

if(SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  target_link_libraries(ObEngine ${EXECUTABLE_NAME} ${SFML_LIBRARIES})
endif()

target_link_libraries(ObEngine ${OPENGL_LIBRARIES})
