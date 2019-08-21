cmake_minimum_required(VERSION 3.8)
set(OpenGL_GL_PREFERENCE GLVND)

project(ObEngine)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)
include(engine_git)

add_subdirectory(extlibs/catch)
add_subdirectory(extlibs/dynamicLinker)
add_subdirectory(extlibs/vili)
add_subdirectory(extlibs/fswrapper)

# fmtlib is required by spdlog
add_subdirectory(extlibs/fmt)
add_subdirectory(extlibs/spdlog)

# lua is required by kaguya
add_subdirectory(extlibs/lua)
add_subdirectory(extlibs/kaguya)

if (APPLE OR USE_FILESYSTEM_FALLBACK)
    add_subdirectory(extlibs/tinydir)
    set(USE_FILESYSTEM_FALLBACK TRUE CACHE BOOL "Use filesystem fallback" FORCE)
endif()

# minizip is required by elzip
add_subdirectory(extlibs/minizip)
add_subdirectory(extlibs/elzip)

# SFML 2.5 is minimum version
find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
# SFML is required by sfe (SFml Extensions)
add_subdirectory(extlibs/sfe)

add_subdirectory(src/Core)

if (BUILD_ANDROID)
    set(BUILD_PLAYER OFF)
    set(BUILD_DEV OFF)
    add_subdirectory(src/Android)
endif()

if (NOT DEFINED BUILD_PLAYER)
    set(BUILD_PLAYER ON CACHE BOOL "Build ObEngine Player ?")
endif()

configure_obengine_git()
if (WIN32)
    file(GLOB OBENGINE_ICON ${CMAKE_SOURCE_DIR}/resources/resource.rc)
else()
    set(OBENGINE_ICON "")
endif()

if (BUILD_PLAYER)
    add_subdirectory(src/Player)
    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ObEnginePlayer)
endif()

if (NOT DEFINED BUILD_DEV)
    set(BUILD_DEV ON CACHE BOOL "Build ObEngine Dev ?")
endif()

if (BUILD_DEV)
    add_subdirectory(extlibs/TGUI)
    add_subdirectory(src/Dev)
    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ObEngineDev)
endif()

if (NOT DEFINED BUILD_TESTS)
    set(BUILD_TESTS OFF CACHE BOOL "Build ObEngine Tests ?")
endif()

if (BUILD_TESTS)
    add_subdirectory(tests)
endif()