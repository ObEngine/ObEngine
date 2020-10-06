cmake_minimum_required(VERSION 3.16)
set(OpenGL_GL_PREFERENCE GLVND)

option(USE_VCPKG "Use vcpkg to handle some of the dependencies" OFF)
if(DEFINED ENV{VCPKG_ROOT} AND NOT DEFINED CMAKE_TOOLCHAIN_FILE
    OR USE_VCPKG)
    set(OBE_USE_VCPKG ON)
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake"
        CACHE STRING "")
endif()

if(OBE_USE_VCPKG)
    if(NOT DEFINED ENV{VCPKG_FEATURE_FLAGS})
        set(ENV{VCPKG_FEATURE_FLAGS} "manifests") # manifests are required because of vcpkg.json
    endif()
        
    if(NOT DEFINED ENV{VCPKG_DEFAULT_TRIPLET})
        message(FATAL_ERROR
            "Using vcpkg to build ObEngine without defining ${VCPKG_DEFAULT_TRIPLET}!! Aborting...")
    endif()
endif()

project(ObEngine)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake)
include(engine_git)

add_subdirectory(extlibs/bezier)

if(NOT OBE_USE_VCPKG)
    add_subdirectory(extlibs/catch)

    # fmtlib is required by spdlog
    add_subdirectory(extlibs/fmt)
    add_subdirectory(extlibs/spdlog)

    # lua is required by sol
    add_subdirectory(extlibs/lua)
    add_subdirectory(extlibs/sol3)
endif()

add_subdirectory(extlibs/dynamicLinker)
add_subdirectory(extlibs/fswrapper)

add_subdirectory(extlibs/vili)

# Audio library
add_subdirectory(extlibs/soloud)

if (APPLE OR USE_FILESYSTEM_FALLBACK AND NOT OBE_USE_VCPKG)
    add_subdirectory(extlibs/tinydir)
    set(USE_FILESYSTEM_FALLBACK TRUE CACHE BOOL "Use filesystem fallback" FORCE)
endif()

# minizip is required by elzip
add_subdirectory(extlibs/minizip)
add_subdirectory(extlibs/elzip)

# snippet taken from
# https://github.com/microsoft/vcpkg/blob/master/ports/sfml/usage
if(OBE_USE_VCPKG)
    include(FindLua)

    find_package(lua REQUIRED)
    find_package(sol2 CONFIG REQUIRED)
    find_package(fmt CONFIG REQUIRED)
    find_package(spdlog CONFIG REQUIRED)
    find_package(Catch2 CONFIG REQUIRED)
    find_path(TINYDIR_INCLUDE_DIRS "tinydir.h")

    find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)

    target_include_directories(ObEngine PRIVATE ${TINYDIR_INCLUDE_DIRS})

    if(WIN32)
        target_link_libraries(ObEngine PRIVATE FLAC OpenAL OpenGL Vorbis)
    else()
        target_link_libraries(ObEngine PRIVATE X11 FLAC UDev OpenAL)
    endif()


    target_link_libraries(ObEngine PRIVATE ${LUA_LIBRARIES})
    target_include_directories(ObEngine PRIVATE ${LUA_INCLUDE_DIR})

    target_link_libraries(ObEngine PRIVATE sol2::sol2)
    target_link_libraries(ObEngine PRIVATE fmt::fmt fmt::fmt-header-only)
    target_link_libraries(ObEngine PRIVATE spdlog::spdlog spdlog::spdlog_header_only)
    target_link_libraries(ObEngine PRIVATE Catch2::Catch2)
    else() # if using built-in dependencies

    # SFML 2.5 is minimum version
    find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
endif()

    # SFML is required by sfe (SFml Extensions)
add_subdirectory(extlibs/sfe)

configure_obengine_git()
add_subdirectory(src/Core)

if (BUILD_ANDROID)
    set(BUILD_PLAYER OFF)
    set(BUILD_DEV OFF)
    add_subdirectory(src/Android)
endif()

if (NOT DEFINED BUILD_PLAYER)
    set(BUILD_PLAYER ON CACHE BOOL "Build ObEngine Player ?")
endif()

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

if (NOT DEFINED BUILD_TESTS)
    set(BUILD_TESTS OFF CACHE BOOL "Build ObEngine Tests ?")
endif()

if (BUILD_TESTS)
    add_subdirectory(tests)
endif()

if (NOT DEFINED RUN_CI_TOOLS)
    set(RUN_CI_TOOLS OFF CACHE BOOL "Run CI tools ?")
endif()

set(CMAKE_CXX_CLANG_TIDY "")
set(CMAKE_CXX_CPPCHECK "")
set(MAKE_CXX_INCLUDE_WHAT_YOU_USE "")
if (RUN_CI_TOOLS)
    find_program(CLANG_TIDY_COMMAND NAMES clang-tidy)
    find_program(CPPCHECK_COMMAND NAMES cppcheck)
    find_program(IWYU_COMMAND NAMES iwyu-tool)

    if (CLANG_TIDY_COMMAND)
        set(CMAKE_CXX_CLANG_TIDY "${CLANG_TIDY_COMMAND};-checks=*,-fuchsia-default-arguments")
    endif()
    if (CPPCHECK_COMMAND)
        set(CMAKE_CXX_CPPCHECK "${CPPCHECK_COMMAND};--std=c++11")
    endif()
    if (IWYU_COMMAND)
        set(MAKE_CXX_INCLUDE_WHAT_YOU_USE "${IWYU_COMMAND};--transitive_includes_only")
    endif()
    set(CMAKE_LINK_WHAT_YOU_USE TRUE)

    get_property(OBENGINE_CORE_SRC TARGET ObEngineCore PROPERTY SOURCES)
    get_property(OBENGINE_PLAYER_SRC TARGET ObEnginePlayer PROPERTY SOURCES)
    get_property(OBENGINE_DEV_SRC TARGET ObEngineDev PROPERTY SOURCES)

    include(clang_format)

    clangformat_setup(
        ${OBENGINE_CORE_SRC}
        ${OBENGINE_PLAYER_SRC}
        ${OBENGINE_DEV_SRC}
    )
endif()