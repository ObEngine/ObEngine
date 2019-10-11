project(Soloud)

file(GLOB SOLOUD_HEADERS include/soloud/*.h)
file(GLOB_RECURSE SOLOUD_SOURCES src/*.c src/*.cpp)

add_library(Soloud ${SOLOUD_HEADERS} ${SOLOUD_SOURCES})

target_include_directories(Soloud
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 11)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_EXTENSIONS OFF)