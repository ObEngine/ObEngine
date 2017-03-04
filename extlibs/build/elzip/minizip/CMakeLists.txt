cmake_minimum_required(VERSION 2.8)
cmake_policy(SET CMP0015 NEW)

project(minizip)

file(GLOB PG_MZIP src/*.h)
file(GLOB HD_MZIP src/*.c)

IF (WIN32)
ELSE()
    list(REMOVE_ITEM PG_MZIP src/iowin32.h)
    list(REMOVE_ITEM HD_MZIP src/iowin32.c)
ENDIF()

add_library(minizip ${PG_MZIP} ${HD_MZIP})