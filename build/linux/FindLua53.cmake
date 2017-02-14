# Locate Lua library
# This module defines
#  LUA53_FOUND, if false, do not try to link to Lua 
#  LUA53_LIBRARIES
#  LUA53_INCLUDE_DIR, where to find lua.h
#  LUA53_VERSION_STRING, the version of Lua found (since CMake 2.8.8)
#
# Note that the expected include convention is
#  #include "lua.h"
# and not
#  #include <lua/lua.h>
# This is because, the lua location is not standardized and may exist
# in locations other than lua/

#=============================================================================
# Copyright 2007-2009 Kitware, Inc.
#
# Distributed under the OSI-approved BSD License (the "License");
# see accompanying file Copyright.txt for details.
#
# This software is distributed WITHOUT ANY WARRANTY; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
# See the License for more information.
#=============================================================================
# (To distribute this file outside of CMake, substitute the full
#  License text for the above reference.)

FIND_PATH(LUA53_INCLUDE_DIR lua.h
  HINTS
  $ENV{LUA_DIR}
  PATH_SUFFIXES include/lua53 include/lua5.3 include/lua include
  PATHS
  ~/Library/Frameworks
  /Library/Frameworks
  /sw # Fink
  /opt/local # DarwinPorts
  /opt/csw # Blastwave
  /opt
)

FIND_LIBRARY(LUA53_LIBRARY
  NAMES lua53 lua5.3 lua-5.3 lua
  HINTS
  $ENV{LUA_DIR}
  PATH_SUFFIXES lib64 lib
  PATHS
  ~/Library/Frameworks
  /Library/Frameworks
  /sw
  /opt/local
  /opt/csw
  /opt
)

IF(LUA53_LIBRARY)
  # include the math library for Unix
  IF(UNIX AND NOT APPLE)
    FIND_LIBRARY(LUA53_MATH_LIBRARY m)
    SET( LUA53_LIBRARIES "${LUA53_LIBRARY};${LUA53_MATH_LIBRARY}" CACHE STRING "Lua Libraries")
  # For Windows and Mac, don't need to explicitly include the math library
  ELSE(UNIX AND NOT APPLE)
    SET( LUA53_LIBRARIES "${LUA53_LIBRARY}" CACHE STRING "Lua Libraries")
  ENDIF(UNIX AND NOT APPLE)
ENDIF(LUA53_LIBRARY)

IF(LUA53_INCLUDE_DIR AND EXISTS "${LUA53_INCLUDE_DIR}/lua.h")
  FILE(STRINGS "${LUA53_INCLUDE_DIR}/lua.h" lua_version_str REGEX "^#define[ \t]+LUA_RELEASE[ \t]+\"Lua .+\"")

  STRING(REGEX REPLACE "^#define[ \t]+LUA_RELEASE[ \t]+\"Lua ([^\"]+)\".*" "\\1" LUA53_VERSION_STRING "${lua_version_str}")
  UNSET(lua_version_str)
ENDIF()

INCLUDE(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set LUA52_FOUND to TRUE if
# all listed variables are TRUE
FIND_PACKAGE_HANDLE_STANDARD_ARGS(Lua53
                                  REQUIRED_VARS LUA53_LIBRARIES LUA53_INCLUDE_DIR
                                  VERSION_VAR LUA53_VERSION_STRING)

MARK_AS_ADVANCED(LUA53_INCLUDE_DIR LUA53_LIBRARIES LUA53_LIBRARY LUA53_MATH_LIBRARY)

