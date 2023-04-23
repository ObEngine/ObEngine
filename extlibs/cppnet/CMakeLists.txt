project(cppnet)

file(GLOB CPPNET_HEADERS CONFIGURE_DEPENDS include/cppnet/*.hpp)
file(GLOB CPPNET_SOURCES CONFIGURE_DEPENDS src/*.cpp)

# add platform specific sources
if(WIN32)
    list(APPEND CPPNET_SOURCES
        src/win32/socket_impl.cpp
        src/win32/socket_impl.hpp
        src/win32/windows_header.hpp
    )
else()
    list(APPEND CPPNET_SOURCES
        src/unix/socket_impl.cpp
        src/unix/socket_impl.hpp
    )
endif()

# define the cppnet target
add_library(cppnet ${CPPNET_HEADERS} ${CPPNET_SOURCES})

target_include_directories(cppnet
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include/cppnet
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# setup dependencies
if(WIN32)
    target_link_libraries(cppnet PRIVATE ws2_32)
endif()

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_EXTENSIONS OFF)