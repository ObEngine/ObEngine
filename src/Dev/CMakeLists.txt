project(ObEngineDev)

include(group_files)
include(setup_environment)

file(GLOB_RECURSE OBEDEV_HEADERS
    ${ObEngine_SOURCE_DIR}/include/Dev/*.hpp)
file(GLOB_RECURSE OBEDEV_SOURCES
    ${ObEngine_SOURCE_DIR}/src/Dev/*.cpp)
file(GLOB_RECURSE OBEPLAYER_GAME_SOURCE
    ${ObEngine_SOURCE_DIR}/src/Player/Modes/Game.cpp)

add_executable(ObEngineDev ${OBEDEV_HEADERS} ${OBEDEV_SOURCES} ${OBEPLAYER_GAME_SOURCE} ${OBENGINE_ICON})

target_include_directories(ObEngineDev
    PRIVATE
        $<BUILD_INTERFACE:${ObEngine_SOURCE_DIR}/include/Player>
        $<BUILD_INTERFACE:${ObEngine_SOURCE_DIR}/include/Dev>
)

target_link_libraries(ObEngineDev ObEngineCore)
target_link_libraries(ObEngineDev TGUI)
target_link_libraries(ObEngineDev sfml-window)

find_package(OpenGL REQUIRED)
target_link_libraries(ObEngineDev ${OPENGL_LIBRARIES})

group_files(
    "${OBEDEV_HEADERS}" "${OBEDEV_SOURCES}"
    "${ObEngine_SOURCE_DIR}/include/Dev"
    "${ObEngine_SOURCE_DIR}/src/Dev"
)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_EXTENSIONS OFF)

set_property(TARGET ObEngineDev PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/engine")

copy_required_dlls(ObEngineDev)