cmake_minimum_required(VERSION 2.8)

project(mse)

file(GLOB PG_MSE include/*.hpp)
file(GLOB HD_MSE src/*.cpp)

ADD_DEFINITIONS(-std=c++14)

set(CMAKE_MODULE_PATH "build/linux" ${CMAKE_MODULE_PATH})
if(CMAKE_COMPILER_IS_GNUCC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fpermissive")
endif()
set_property(GLOBAL APPEND_STRING PROPERTY COMPILE_FLAGS -Wall )
find_package(SFML 2 REQUIRED system window graphics network audio)
find_package(OpenGL REQUIRED)
find_package(Lua53 REQUIRED) 

add_executable(mse ${PG_MSE} ${HD_MSE})

include_directories(${LUA53_INCLUDE_DIR})
include_directories("build/libs/kaguya/include")
include_directories(${OPENGL_INCLUDE_DIR})
if(SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  target_link_libraries(mse ${EXECUTABLE_NAME} ${SFML_LIBRARIES})
endif()
target_link_libraries(mse ${LUA53_LIBRARIES})
target_link_libraries(mse ${OPENGL_LIBRARIES})
