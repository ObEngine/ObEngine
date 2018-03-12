cmake_minimum_required(VERSION 3.6)

project(ObEngineTests)

file(GLOB_RECURSE OBT_HEADERS src/*.hpp)
file(GLOB_RECURSE OBT_SOURCES src/*.cpp)

FOREACH(item ${OBT_SOURCES})
  IF(${item} MATCHES "ObEngine.cpp")
    LIST(REMOVE_ITEM OBT_SOURCES ${item})
  ENDIF(${item} MATCHES "ObEngine.cpp")
ENDFOREACH(item)

find_package(OpenGL REQUIRED)

add_executable(ObEngineTests ${OBT_HEADERS} ${OBT_SOURCES})

target_include_directories(ObEngineTests
  PRIVATE
    $<BUILD_INTERFACE:${SFML_INCLUDE_DIR}>
    $<BUILD_INTERFACE:${OPENGL_INCLUDE_DIR}>
)

target_link_libraries(ObEngineTests ObEngineCore)
target_link_libraries(ObEngineTests catch)
target_link_libraries(ObEngineTests elzip)
target_link_libraries(ObEngineTests lua)
target_link_libraries(ObEngineTests sfe)
target_link_libraries(ObEngineTests vili)
target_link_libraries(ObEngineTests dynamicLinker)

if (UNIX)
    target_link_libraries(ObEngineTests ${CMAKE_DL_LIBS})
endif()

if(SFML_FOUND)
  target_link_libraries(ObEngineTests ${EXECUTABLE_NAME} ${SFML_LIBRARIES})
endif()

target_link_libraries(ObEngineTests ${OPENGL_LIBRARIES})

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_EXTENSIONS OFF)

if (MSVC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++latest")
endif (MSVC)