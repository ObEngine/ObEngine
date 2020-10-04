function (set_git_version BRANCH HASH VERSION_UNFORMATTED)
    set(OBENGINE_GIT_BRANCH ${BRANCH} CACHE STRING "ObEngine git branch" FORCE)
    set(OBENGINE_GIT_COMMIT_HASH ${HASH} CACHE STRING "ObEngine git commit hash" FORCE)

    string(REGEX MATCH "v(.+)\.(.+)\.(.+)$" VERSION "${VERSION_UNFORMATTED}")

    set(OBENGINE_VERSION ${VERSION} CACHE STRING "ObEngine version string" FORCE)
    set(VERSION_MAJOR ${CMAKE_MATCH_1})
    set(VERSION_MINOR ${CMAKE_MATCH_2})
    set(VERSION_PATCH ${CMAKE_MATCH_3})

    string(REGEX MATCH "([0-9]+)$" RES ${VERSION_MAJOR})
    if(NOT ${RES} STREQUAL "")
        set(VERSION_MAJOR ${CMAKE_MATCH_1})
        # 0*([0-9]+)$ seems nicer, but CMake can not lazily match
        math(EXPR VERSION_MAJOR "${VERSION_MAJOR} * 1")
    else()
        set(VERSION_MAJOR "-1")
    endif()

    string(REGEX MATCH "([0-9]+)$" RES ${VERSION_MINOR})
    if(NOT ${RES} STREQUAL "")
        set(VERSION_MINOR ${CMAKE_MATCH_1})
        math(EXPR VERSION_MINOR "${VERSION_MINOR} * 1")
    else()
        set(VERSION_MINOR "-1")
    endif()

    string(REGEX MATCH "([0-9]+)$" RES ${VERSION_PATCH})
    if(NOT ${RES} STREQUAL "")
        set(VERSION_PATCH ${CMAKE_MATCH_1})
        math(EXPR VERSION_PATCH "${VERSION_PATCH} * 1")
    else()
        set(VERSION_PATCH "-1")
    endif()

    set(OBENGINE_VERSION_MAJOR ${VERSION_MAJOR} CACHE STRING "ObEngine major version" FORCE)
    set(OBENGINE_VERSION_MINOR ${VERSION_MINOR} CACHE STRING "ObEngine minor version" FORCE)
    set(OBENGINE_VERSION_PATCH ${VERSION_PATCH} CACHE STRING "ObEngine patch version" FORCE)
endfunction()

function (configure_obengine_git)
    find_package(Git QUIET)
    message(STATUS "Configure Git variables for ÖbEngine")
    if (Git_FOUND)
        execute_process(
            COMMAND ${GIT_EXECUTABLE} rev-parse --is-inside-work-tree
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
            OUTPUT_VARIABLE IS_CMAKE_SOURCE_DIR_A_GIT_DIRECTORY
            OUTPUT_STRIP_TRAILING_WHITESPACE
            ERROR_VARIABLE _testOut
        )
        if (${IS_CMAKE_SOURCE_DIR_A_GIT_DIRECTORY})
            # Get the git branch name
            execute_process(
                COMMAND ${GIT_EXECUTABLE} rev-parse --abbrev-ref HEAD
                WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
                OUTPUT_VARIABLE GIT_BRANCH
                OUTPUT_STRIP_TRAILING_WHITESPACE
            )

            # Get the latest abbreviated commit hash of the working branch
            execute_process(
                COMMAND ${GIT_EXECUTABLE} log -1 --format=%H
                WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
                OUTPUT_VARIABLE GIT_COMMIT_HASH
                OUTPUT_STRIP_TRAILING_WHITESPACE
            )
            message(STATUS "Git commit hash ${GIT_COMMIT_HASH}")

            # Get the version tag from git
            execute_process(
                COMMAND ${GIT_EXECUTABLE} for-each-ref refs/tags --sort=-taggerdate --count=1
                WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
                OUTPUT_VARIABLE GIT_OBENGINE_VERSION_UNFORMATTED
                OUTPUT_STRIP_TRAILING_WHITESPACE
            )

            set_git_version("${GIT_BRANCH}" "${GIT_COMMIT_HASH}" "${GIT_OBENGINE_VERSION_UNFORMATTED}")
            message(STATUS "ÖbEngine Git version : ${OBENGINE_GIT_BRANCH}:${OBENGINE_GIT_COMMIT_HASH}")
            message(STATUS "ÖbEngine version : ${OBENGINE_VERSION}")
        else()
            message(WARNING "ObEngine CMake's source dir is not a git directory, ÖbEngine won't have version available and it can cause some problems.\n"
                "Clone ObEngine properly or set the following variables : OBENGINE_GIT_BRANCH, OBENGINE_GIT_COMMIT_HASH, OBENGINE_VERSION.")
            set_git_version("unknown" "unknown" "v?.?.?")
        endif()
    else()
        message(WARNING "You do not have git installed, ÖbEngine won't have version available and it can cause some problems.\n"
            "Install git or set the following variables : OBENGINE_GIT_BRANCH, OBENGINE_GIT_COMMIT_HASH, OBENGINE_VERSION.")
        set_git_version("unknown" "unknown" "v?.?.?")
    endif()
endfunction()