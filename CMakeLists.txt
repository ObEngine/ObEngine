cmake_minimum_required(VERSION 3.6)

project(ObEngine)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)

add_subdirectory(extlibs/catch)
add_subdirectory(extlibs/dynamicLinker)
add_subdirectory(extlibs/vili)

add_subdirectory(extlibs/fmt)
add_subdirectory(extlibs/spdlog)

add_subdirectory(extlibs/lua)
add_subdirectory(extlibs/kaguya)

add_subdirectory(extlibs/minizip)
add_subdirectory(extlibs/elzip)

find_package(SFML 2 REQUIRED graphics window system network audio)
find_package(OpenGL REQUIRED)
add_subdirectory(extlibs/sfe)

add_subdirectory(src/Core)

IF (NOT DEFINED BUILD_PLAYER)
    set(BUILD_PLAYER ON CACHE BOOL "Build ObEngine Player ?")
ENDIF()

if(BUILD_PLAYER)
    add_subdirectory(src/Player)
    
    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ObEnginePlayer)
endif()

IF (NOT DEFINED BUILD_DEV)
    set(BUILD_DEV ON CACHE BOOL "Build ObEngine Dev ?")
ENDIF()

if(BUILD_DEV)
	find_package(Qt5 COMPONENTS Core Quick REQUIRED)
	set(CMAKE_AUTOMOC ON)
	set(CMAKE_AUTORCC ON)
	set (CMAKE_INCLUDE_CURRENT_DIR ON)

    add_subdirectory(extlibs/TGUI)

    add_subdirectory(src/Dev)
    
    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ObEngineDev)
endif()

IF (NOT DEFINED BUILD_TESTS)
    set(BUILD_TESTS OFF CACHE BOOL "Build ObEngine Tests ?")
ENDIF()

if(BUILD_TESTS)
    add_subdirectory(tests)
endif()