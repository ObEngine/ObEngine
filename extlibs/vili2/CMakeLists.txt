cmake_minimum_required(VERSION 3.6)

project(vili2)

add_subdirectory(extlibs/pegtl)

set(VILI2_HEADERS
    include/vili2/config.hpp
    include/vili2/exceptions.hpp
    include/vili2/node.hpp
    include/vili2/types.hpp
    include/vili2/utils.hpp
    include/vili2/parser/actions.hpp
    include/vili2/parser/grammar.hpp
    include/vili2/parser/parser_state.hpp
    include/vili2/parser/parser.hpp
)
set(VILI2_SOURCES
    src/node.cpp
    src/types.cpp
    src/utils.cpp
    src/parser/parser_state.cpp
    src/parser/parser.cpp
)

add_library(vili2 ${VILI2_HEADERS} ${VILI2_SOURCES})

target_link_libraries(vili2 fmt)
target_link_libraries(vili2 pegtl)

set(VILI_KEEP_ORDER ON CACHE BOOL "Keep insertion order ?")

if (VILI_KEEP_ORDER)
    add_subdirectory(extlibs/tsl)
    target_link_libraries(vili2 tsl)
    target_compile_definitions(vili2 PRIVATE VILI_KEEP_ORDER)
endif()

target_include_directories(vili2
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_EXTENSIONS OFF)