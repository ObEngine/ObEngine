cmake_minimum_required(VERSION 3.6)

project(catch)

file(GLOB CATCH_HEADERS include/catch/catch.hpp)

add_library(catch INTERFACE)

target_include_directories(catch INTERFACE $<INSTALL_INTERFACE:include>)
