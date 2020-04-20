project(dynamicLinker)

file(GLOB DYLINK_HEADERS include/dynamicLinker/*.hpp)
file(GLOB DYLINK_SOURCES src/*.cpp)

add_library(dynamicLinker ${DYLINK_HEADERS} ${DYLINK_SOURCES})

target_include_directories(dynamicLinker
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include/dynamicLinker
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

if (UNIX)
    target_link_libraries(dynamicLinker ${CMAKE_DL_LIBS})
endif()

if (CMAKE_COMPILER_IS_GNUCXX AND CMAKE_CXX_COMPILER_VERSION VERSION_LESS 4.8.2)
    message(FATAL_ERROR
    "GCC with version less than 4.8.2 is known to cause a crash with dynamicLinker lib, please update your compiler")
endif()

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 11)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_EXTENSIONS OFF)