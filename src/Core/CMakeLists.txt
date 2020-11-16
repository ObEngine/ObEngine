project(ObEngineCore)

include(group_files)

add_custom_target(ConfigureObEngineGit COMMAND ${CMAKE_COMMAND} 
    -DGIT_EXECUTABLE=${GIT_EXECUTABLE} -DObEngine_SOURCE_DIR=${ObEngine_SOURCE_DIR} -DObEngine_BINARY_DIR=${ObEngine_BINARY_DIR} -P "${ObEngine_SOURCE_DIR}/cmake/engine_git.cmake")

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
    find_package(spdlog CONFIG REQUIRED)

    find_package(sol2 CONFIG REQUIRED)
    find_package(Catch2 CONFIG REQUIRED)

    target_include_directories(ObEngineCore PUBLIC
        $ENV{VCPKG_ROOT}/installed/$ENV{VCPKG_DEFAULT_TRIPLET}/include)

    if (USE_FILESYSTEM_FALLBACK)
        target_include_directories(ObEngineCore ${TINYDIR_INCLUDE_DIRS})
    endif()


    target_link_libraries(ObEngineCore ${LUA_LIBRARIES}
        ConfigureObEngineGit bezier elzip sfe vili dynamicLinker Soloud
        sol2::sol2 fmt::fmt spdlog::spdlog Catch2::Catch2)
    target_include_directories(ObEngineCore PRIVATE ${LUA_INCLUDE_DIR})
else()
    target_link_libraries(ObEngineCore
        lua sol3 fmt spdlog)
    target_link_libraries(ObEngineCore sfml-graphics sfml-system sfml-network)
endif()    

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
