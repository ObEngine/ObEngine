if(CMAKE_SYSTEM_NAME MATCHES "Android")
    cmake_minimum_required(VERSION 3.7)  # CMake's built-in Android support requires 3.7
else()
    cmake_minimum_required(VERSION 3.5)  # Can be at most 3.5.1 as long as Ubuntu 16.04 is supported
endif()

# Use new RPATH behavior on macOS (CMake 3.9 and newer)
if(POLICY CMP0068)
    cmake_policy(SET CMP0068 NEW)
endif()

# Don't warn about existence of SFML_ROOT variable (CMake 3.12 and newer)
if(POLICY CMP0074)
    cmake_policy(SET CMP0074 NEW)
endif()

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/Macros.cmake)

# Set a default build type
tgui_set_option(CMAKE_BUILD_TYPE Release STRING "Choose the type of build (Debug or Release)")

# Set CMAKE_MODULE_PATH to find SFML < 2.5 without manually having to specify a module path
if(NOT SFML_DIR AND NOT CMAKE_MODULE_PATH)
    set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules")
endif()

# Project name and version
project(TGUI VERSION 0.8.6)

# TGUI uses the paths from the cmake GNUInstallDirs module as defaults (https://cmake.org/cmake/help/v3.0/module/GNUInstallDirs.html)
include(GNUInstallDirs)

# Include the configuration file
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/Config.cmake)

# Add an option for choosing the build type (shared or static)
set(TGUI_SHARED_LIBS FALSE)
if (TGUI_OS_IOS OR TGUI_OS_ANDROID)
    if(TGUI_OS_IOS)
        set(TGUI_SHARED_LIBS FALSE)
    elseif(TGUI_OS_ANDROID)
        set(TGUI_SHARED_LIBS TRUE)
    endif()
endif()

tgui_set_option(TGUI_CXX_STANDARD "14" STRING "C++ standard version to build TGUI with. Possible values: 14, 17 or 20. Projects using TGUI must use a version equal or higher to this")

# At least c++14 has to be used
if (TGUI_CXX_STANDARD LESS "14")
    message(FATAL_ERROR "TGUI_CXX_STANDARD has to be at least 14")
else()
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/include/TGUI/Config.hpp.in ${CMAKE_CURRENT_SOURCE_DIR}/include/TGUI/Config.hpp @ONLY)
endif()

# Mac OS X specific options
if(TGUI_OS_MACOSX)
    # Only the default architecture (i.e. 64-bit) is supported
    if(CMAKE_OSX_ARCHITECTURES AND NOT "${CMAKE_OSX_ARCHITECTURES}" STREQUAL "x86_64")
        message(FATAL_ERROR "Only 64-bit architecture is supported")
        return()
    endif()

    # Enable to use of rpath according to CMake Policy CMP0042
    set(CMAKE_MACOSX_RPATH 1)
endif()

# Android options
if(TGUI_OS_ANDROID)

    # Make sure there's the android library available
    if(CMAKE_ANDROID_API LESS 19)
        message(FATAL_ERROR "Android API level (${CMAKE_ANDROID_API}) must be equal or greater than 19.")
    endif()

    # CMake doesn't support defining the STL to be used with Nsight Tegra, so warn the user
    if(CMAKE_VS_PLATFORM_NAME STREQUAL "Tegra-Android")
        message(WARNING "CMake might not properly support setting the STL. Make sure to adjust all generated library projects!")
    endif()

    # Install everything in $NDK/sources/third_party by default
    if (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
        set(CMAKE_INSTALL_PREFIX ${CMAKE_ANDROID_NDK}/sources/third_party/tgui CACHE PATH "Installation path (should be inside your NDK's 'sources' directory)" FORCE)
    endif()

    # We install libs in a subdirectory named after the ABI (e.g. lib/armeabi/libtgui.so)
    set(CMAKE_INSTALL_LIBDIR "${CMAKE_INSTALL_LIBDIR}/${CMAKE_ANDROID_ARCH_ABI}")
endif()

# Add an option to choose whether PDB debug symbols should be generated for Visual Studio
if(TGUI_COMPILER_MSVC)
    tgui_set_option(TGUI_GENERATE_PDB TRUE BOOL "True to generate PDB debug symbols, FALSE otherwise.")
endif()

# Apply the TGUI_USE_STATIC_STD_LIBS option on windows when using VC++
# This can't be done in the tgui_set_stdlib macro because it is too late to change these variables by then
if(TGUI_OS_WINDOWS AND TGUI_COMPILER_MSVC AND TGUI_USE_STATIC_STD_LIBS)
    foreach(flag
            CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE
            CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELWITHDEBINFO)
        if(${flag} MATCHES "/MD")
            string(REGEX REPLACE "/MD" "/MT" ${flag} "${${flag}}")
        endif()
    endforeach()
endif()

# Attempt to find the SFML dependencies when linking statically
if(NOT TGUI_SHARED_LIBS)
    if(SFML_ROOT)
        if(TGUI_OS_WINDOWS)
            set(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "${SFML_ROOT}/extlibs/headers")
            if(ARCH_32BITS)
                if(TGUI_COMPILER_MSVC AND MSVC_VERSION LESS 1900) # older than VC++14
                    set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "${SFML_ROOT}/extlibs/libs-msvc/x86")
                elseif(TGUI_COMPILER_MSVC) # VC++14 or newer
                    set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "${SFML_ROOT}/extlibs/libs-msvc-universal/x86")
                else() # gcc
                    set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "${SFML_ROOT}/extlibs/libs-mingw/x86")
                endif()
            elseif(ARCH_64BITS)
                if(TGUI_COMPILER_MSVC AND MSVC_VERSION LESS 1900) # older than VC++14
                    set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "${SFML_ROOT}/extlibs/libs-msvc/x64")
                elseif(TGUI_COMPILER_MSVC) # VC++14 or newer
                    set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "${SFML_ROOT}/extlibs/libs-msvc-universal/x64")
                else() # gcc
                    set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "${SFML_ROOT}/extlibs/libs-mingw/x64")
                endif()
            endif()
        elseif(TGUI_OS_MACOSX)
            set(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "${SFML_ROOT}/extlibs/headers")
            set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "${SFML_ROOT}/extlibs/libs-osx/lib/")
        elseif(TGUI_OS_ANDROID)
            set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "${CMAKE_ANDROID_NDK}/sources/third_party/sfml/extlibs/lib/${CMAKE_ANDROID_ARCH_ABI}/")
        elseif(TGUI_OS_IOS)
            set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "${SFML_ROOT}/extlibs/libs-ios/")
        endif()
    endif()
endif()

# Find sfml if not build in same project
if(NOT TARGET sfml-graphics)
    if(TGUI_OS_WINDOWS AND TGUI_COMPILER_MSVC) # Also look for the main component when using Visual Studio
        find_package(SFML 2 COMPONENTS main graphics window system)
    elseif(TGUI_OS_ANDROID)  # Search for SFML in the android NDK (if no other directory is specified)
        find_package(SFML 2 COMPONENTS graphics window system PATHS "${CMAKE_ANDROID_NDK}/sources/third_party/sfml/lib/${CMAKE_ANDROID_ARCH_ABI}/cmake/SFML")
    elseif(TGUI_OS_IOS)  # Use the find_host_package macro from the toolchain on iOS
        find_host_package(SFML 2 COMPONENTS main graphics window system)
    else()
        find_package(SFML 2 COMPONENTS graphics window system)
    endif()

    # find_package couldn't find SFML
    if(NOT SFML_FOUND)
        set(SFML_DIR "" CACHE PATH "Path to SFMLConfig.cmake")
        set(SFML_ROOT "" CACHE PATH "SFML root directory")
        message(FATAL_ERROR "CMake couldn't find SFML.\nEither set SFML_DIR to the directory containing SFMLConfig.cmake or set the SFML_ROOT entry to SFML's root directory (containing \"include\" and \"lib\" directories).")
    endif()
endif()

# Set the path for the libraries
set(LIBRARY_OUTPUT_PATH "${PROJECT_BINARY_DIR}/lib")

# Jump to the CMakeLists.txt file in the source folder
add_subdirectory(src/TGUI)