cmake_minimum_required(VERSION 3.3)

project(lunasvg VERSION 2.3.0 LANGUAGES CXX C)

option(BUILD_SHARED_LIBS "Builds as shared library" OFF)
option(LUNASVG_BUILD_EXAMPLES "Builds examples" OFF)

add_library(lunasvg)

add_subdirectory(include)
add_subdirectory(source)
add_subdirectory(3rdparty/software)
add_subdirectory(3rdparty/plutovg)

if(BUILD_SHARED_LIBS)
    target_compile_definitions(lunasvg PUBLIC LUNASVG_SHARED)
    target_compile_definitions(lunasvg PRIVATE LUNASVG_EXPORT)
endif()

if(LUNASVG_BUILD_EXAMPLES)
    add_subdirectory(example)
endif()

set(LUNASVG_LIBDIR ${CMAKE_INSTALL_PREFIX}/lib)
set(LUNASVG_INCDIR ${CMAKE_INSTALL_PREFIX}/include)

install(FILES
    include/lunasvg.h
    DESTINATION ${LUNASVG_INCDIR}
)

install(TARGETS lunasvg
    LIBRARY     DESTINATION    ${LUNASVG_LIBDIR}
    ARCHIVE     DESTINATION    ${LUNASVG_LIBDIR}
    INCLUDES    DESTINATION    ${LUNASVG_INCDIR}
)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 14)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_EXTENSIONS OFF)