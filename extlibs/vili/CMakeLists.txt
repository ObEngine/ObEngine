cmake_minimum_required(VERSION 3.6)

project(vili)

add_subdirectory(extlibs/fifo_map)
add_subdirectory(extlibs/pegtl)

set(VILI_HEADERS
    include/vili/config.hpp
    include/vili/exceptions.hpp
    include/vili/node.hpp
    include/vili/types.hpp
    include/vili/utils.hpp
    include/vili/parser/actions.hpp
    include/vili/parser/grammar.hpp
    include/vili/parser/grammar_errors.hpp
    include/vili/parser/parser_state.hpp
    include/vili/parser/parser.hpp
)
set(VILI_SOURCES
    src/node.cpp
    src/types.cpp
    src/utils.cpp
    src/parser/parser_state.cpp
    src/parser/parser.cpp
)

add_library(vili ${VILI_HEADERS} ${VILI_SOURCES})

target_link_libraries(vili fifo_map)
target_link_libraries(vili fmt)
target_link_libraries(vili pegtl)

target_include_directories(vili
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