project(ObEnginePlayer)

include(group_files)
include(setup_environment)

file(GLOB_RECURSE OBEPLAYER_HEADERS "${ObEngine_SOURCE_DIR}/include/Player/*.hpp")
file(GLOB_RECURSE OBEPLAYER_SOURCES "${ObEngine_SOURCE_DIR}/src/Player/*.cpp")

if (BUILD_ANDROID)
    add_library(ObEnginePlayer SHARED ${OBEPLAYER_HEADERS} ${OBEPLAYER_SOURCES})
else()
    add_executable(ObEnginePlayer ${OBEPLAYER_HEADERS} ${OBEPLAYER_SOURCES} ${OBENGINE_ICON})
endif()

target_include_directories(ObEnginePlayer
    PRIVATE
        $<BUILD_INTERFACE:${ObEngine_SOURCE_DIR}/include/Player>
)

target_link_libraries(ObEnginePlayer ObEngineCore)
target_link_libraries(ObEnginePlayer sfml-window)

group_files(
    "${OBEPLAYER_HEADERS}" "${OBEPLAYER_SOURCES}"
    "${ObEngine_SOURCE_DIR}/include/Player"
    "${ObEngine_SOURCE_DIR}/src/Player"
)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_EXTENSIONS OFF)

set_property(TARGET ObEnginePlayer PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/engine")

copy_required_dlls(ObEnginePlayer)