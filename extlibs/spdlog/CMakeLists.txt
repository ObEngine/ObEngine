project(spdlog)

file(GLOB SPDLOG_HEADERS 
    include/spdlog/*.h 
    include/spdlog/details/*.h 
    include/spdlog/fmt/*.h 
    include/spdlog/sinks/*.h
)

add_library(spdlog INTERFACE)
target_compile_definitions(spdlog INTERFACE SPDLOG_FMT_EXTERNAL)
target_link_libraries(spdlog INTERFACE fmt)
#target_link_libraries(spdlog INTERFACE log)
target_include_directories(spdlog
    INTERFACE
        $<INSTALL_INTERFACE:include>    
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)
