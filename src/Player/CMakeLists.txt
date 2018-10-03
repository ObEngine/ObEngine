project(ObEnginePlayer)

include(group_files)

file(GLOB_RECURSE OBEPLAYER_HEADERS "${ObEngine_SOURCE_DIR}/include/Player/*.hpp")
file(GLOB_RECURSE OBEPLAYER_SOURCES "${ObEngine_SOURCE_DIR}/src/Player/*.cpp")

add_executable(ObEnginePlayer ${OBEPLAYER_HEADERS} ${OBEPLAYER_SOURCES})

compile_obengine_git_definitions()

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