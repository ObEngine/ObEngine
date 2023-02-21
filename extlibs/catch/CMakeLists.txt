project(catch)

file(GLOB CATCH_HEADERS include/catch_amalgamated.hpp)
file(GLOB CATCH_SOURCES src/catch_amalgamated.cpp)

add_library(catch ${CATCH_HEADERS} ${CATCH_SOURCES})
add_library(Catch2::Catch2 ALIAS catch)

target_include_directories(catch
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_EXTENSIONS OFF)