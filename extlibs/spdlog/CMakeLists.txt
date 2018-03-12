cmake_minimum_required(VERSION 3.6)

project(spdlog)

file(GLOB SPDLOG_HEADERS 
    include/spdlog/*.h 
    include/spdlog/details/*.h 
    include/spdlog/fmt/*.h 
    include/spdlogsinks/*.h
)

add_library(spdlog INTERFACE)

target_compile_definitions(spdlog INTERFACE SPDLOG_FMT_EXTERNAL)
target_include_directories(spdlog
    INTERFACE
        $<INSTALL_INTERFACE:include>    
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)
