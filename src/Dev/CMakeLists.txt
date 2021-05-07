project(ObEngineDev)

include(group_files)
include(setup_environment)

file(GLOB_RECURSE OBEDEV_HEADERS "${ObEngine_SOURCE_DIR}/include/Dev/*.hpp")
file(GLOB_RECURSE OBEDEV_SOURCES "${ObEngine_SOURCE_DIR}/src/Dev/*.cpp")

if (BUILD_ANDROID)
    add_library(ObEngineDev SHARED ${OBEDEV_HEADERS} ${OBEDEV_SOURCES})
else()
    add_executable(ObEngineDev ${OBEDEV_HEADERS} ${OBEDEV_SOURCES} ${OBENGINE_ICON})
endif()

target_include_directories(ObEngineDev
    PRIVATE
        $<BUILD_INTERFACE:${ObEngine_SOURCE_DIR}/include/Dev>
)

target_link_libraries(ObEngineDev ObEngineCore)
target_link_libraries(ObEngineDev sfml-window)
target_link_libraries(ObEngineDev tgui)

group_files(
    "${OBEDEV_HEADERS}" "${OBEDEV_SOURCES}"
    "${ObEngine_SOURCE_DIR}/include/Dev"
    "${ObEngine_SOURCE_DIR}/src/Dev"
)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_EXTENSIONS OFF)

if (MSVC)
    if (NOT (MSVC_VERSION LESS 1910))
        target_compile_options(ObEngineDev PRIVATE /permissive-)
    endif()
endif()

set_property(TARGET ObEngineDev PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/engine")

copy_required_dlls(ObEngineDev)