cmake_minimum_required(VERSION 2.8)
cmake_policy(SET CMP0015 NEW)

project(minizip)

file(GLOB PG_MZIP src/*.h)
file(GLOB HD_MZIP src/*.c)

add_library(minizip ${PG_MZIP} ${HD_MZIP})