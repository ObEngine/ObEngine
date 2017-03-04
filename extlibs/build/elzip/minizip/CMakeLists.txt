cmake_minimum_required(VERSION 2.8)
cmake_policy(SET CMP0015 NEW)

project(minizip)

IF (WIN32)
    file(RENAME src/iowin32.hw src/iowin32.h)
    file(RENAME src/iowin32.cw src/iowin32.c)
ENDIF()

file(GLOB PG_MZIP src/*.h)
file(GLOB HD_MZIP src/*.c)

add_library(minizip ${PG_MZIP} ${HD_MZIP})