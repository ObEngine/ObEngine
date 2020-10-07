project(ObEngineCore)

include(group_files)

file(GLOB_RECURSE OBE_HEADERS
    ${ObEngine_SOURCE_DIR}/include/Core/*.hpp
    ${ObEngine_SOURCE_DIR}/include/Core/*.inl)
list(REMOVE_ITEM OBE_HEADERS "${ObEngine_SOURCE_DIR}/include/Core/PreCompileHeader.hpp")
file(GLOB_RECURSE OBE_SOURCES ${ObEngine_SOURCE_DIR}/src/Core/*.cpp)

add_library(ObEngineCore ${OBE_HEADERS} ${OBE_SOURCES})

target_precompile_headers(ObEngineCore PRIVATE ${ObEngine_SOURCE_DIR}/include/Core/PreCompileHeader.hpp)

if (${BUILD_PLAYER} OR ${BUILD_DEV})
    target_compile_definitions(ObEngineCore PUBLIC OBE_IS_NOT_PLUGIN)
endif()

target_include_directories(ObEngineCore
    PUBLIC
        $<INSTALL_INTERFACE:${ObEngine_SOURCE_DIR}/include/Core>
        $<BUILD_INTERFACE:${ObEngine_SOURCE_DIR}/include/Core>
        $<BUILD_INTERFACE:${ObEngine_BINARY_DIR}/include/Core>
)

if(OBE_USE_VCPKG)
    if (USE_FILESYSTEM_FALLBACK)
        target_include_directories(ObEngineCore ${TINYDIR_INCLUDE_DIRS})
    endif()

    if(WIN32)
        target_link_libraries(ObEngineCore FLAC OpenAL OpenGL Vorbis)
    else()
        target_link_libraries(ObEngineCore X11 FLAC UDev OpenAL)
    endif()


    target_link_libraries(ObEngineCore ${LUA_LIBRARIES})
    target_include_directories(ObEngineCore ${LUA_INCLUDE_DIR})

    target_link_libraries(ObEngineCore sol2::sol2)
    target_link_libraries(ObEngineCore fmt::fmt)
    target_link_libraries(ObEngineCore spdlog::spdlog)
    target_link_libraries(ObEngineCore Catch2::Catch2)
else()
    target_link_libraries(ObEngineCore lua)
    target_link_libraries(ObEngineCore sol3)

    target_link_libraries(ObEngineCore spdlog)
    target_link_libraries(ObEngineCore fmt)
    target_link_libraries(ObEngineCore sfml-graphics sfml-system sfml-network)
    
endif()

target_link_libraries(ObEngineCore bezier)
target_link_libraries(ObEngineCore elzip)
target_link_libraries(ObEngineCore sfe)
target_link_libraries(ObEngineCore vili)
target_link_libraries(ObEngineCore dynamicLinker)
target_link_libraries(ObEngineCore Soloud)

if (USE_FILESYSTEM_FALLBACK)
    message("Using filesystem fallback")
    if(NOT OBE_USE_VCPKG)
        target_link_libraries(ObEngineCore tinydir)
    endif()
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

if (MSVC)
    if (NOT (MSVC_VERSION LESS 1920))
        target_compile_options(ObEngineCore PRIVATE /permissive- /bigobj /MP)
    else()
        target_compile_options(ObEngineCore PRIVATE /MP)
    endif()
endif()

function (apply_git_variables)
    target_compile_definitions(${PROJECT_NAME} PUBLIC OBENGINE_GIT_BRANCH="${OBENGINE_GIT_BRANCH}")
    target_compile_definitions(${PROJECT_NAME} PUBLIC OBENGINE_GIT_HASH="${OBENGINE_GIT_COMMIT_HASH}")
    target_compile_definitions(${PROJECT_NAME} PUBLIC OBENGINE_VERSION="${OBENGINE_VERSION}")
endfunction()

configure_file(
    "${ObEngine_SOURCE_DIR}/include/Core/Config/Git.hpp.in"
    "${ObEngine_BINARY_DIR}/include/Core/Config/Git.hpp"
)
