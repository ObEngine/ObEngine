cmake_minimum_required(VERSION 3.6)
cmake_policy(SET CMP0015 NEW)

project(minizip)

IF (WIN32)
    MESSAGE("Using iowin32")
    file(GLOB PG_MZIP 
        src/win/*.h
        src/*.h
    )
    file(GLOB HD_MZIP 
        src/win/*.c
        src/*.c
    )
ELSE()
    MESSAGE("Not using iowin32")
    file(GLOB PG_MZIP src/*.h)
    file(GLOB HD_MZIP src/*.c)
ENDIF()

add_library(minizip ${PG_MZIP} ${HD_MZIP})