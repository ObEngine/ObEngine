project(ObEngineCore)

include(group_files)

file(GLOB_RECURSE OBE_HEADERS 
    ${ObEngine_SOURCE_DIR}/include/Core/*.hpp 
    ${ObEngine_SOURCE_DIR}/include/Core/*.inl)
file(GLOB_RECURSE OBE_SOURCES ${ObEngine_SOURCE_DIR}/src/Core/*.cpp)

add_library(ObEngineCore ${OBE_HEADERS} ${OBE_SOURCES})

if (${BUILD_PLAYER} OR ${BUILD_DEV})
    target_compile_definitions(ObEngineCore PUBLIC OBE_IS_NOT_PLUGIN)
endif()

target_include_directories(ObEngineCore
    PUBLIC
        $<INSTALL_INTERFACE:${ObEngine_SOURCE_DIR}/include/Core>
        $<BUILD_INTERFACE:${ObEngine_SOURCE_DIR}/include/Core>
)

target_link_libraries(ObEngineCore elzip)
target_link_libraries(ObEngineCore lua)
target_link_libraries(ObEngineCore sfe)
target_link_libraries(ObEngineCore vili)
target_link_libraries(ObEngineCore dynamicLinker)
target_link_libraries(ObEngineCore spdlog)
target_link_libraries(ObEngineCore fmt)
target_link_libraries(ObEngineCore kaguya)
target_link_libraries(ObEngineCore sfml-graphics sfml-audio sfml-system sfml-network)

if (USE_FILESYSTEM_FALLBACK)
    message("Using filesystem fallback")
    target_link_libraries(ObEngineCore tinydir)
    target_compile_definitions(ObEngineCore PUBLIC _USE_FILESYSTEM_FALLBACK)
elseif (CMAKE_COMPILER_IS_GNUCXX)
    target_link_libraries(ObEngineCore stdc++fs)
endif()

group_files(
    "${OBE_HEADERS}" "${OBE_SOURCES}"
    "${ObEngine_SOURCE_DIR}/include/Core"
    "${ObEngine_SOURCE_DIR}/src/Core"
)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_EXTENSIONS OFF)