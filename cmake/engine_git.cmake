function (set_git_version BRANCH HASH VERSION)
    set(OBENGINE_GIT_BRANCH ${BRANCH} CACHE STRING "ObEngine git branch" FORCE)
    set(OBENGINE_GIT_COMMIT_HASH ${HASH} CACHE STRING "ObEngine git commit hash" FORCE)
    set(OBENGINE_VERSION ${VERSION} CACHE STRING "ObEngine version" FORCE)
endfunction()

function (configure_obengine_git)
    find_program(GIT_FOUND git)
    message("Configure Git variables for ÖbEngine")
    if (GIT_FOUND)
        execute_process(
            COMMAND git rev-parse --is-inside-work-tree
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
            OUTPUT_VARIABLE IS_CMAKE_SOURCE_DIR_A_GIT_DIRECTORY
            OUTPUT_STRIP_TRAILING_WHITESPACE
            ERROR_VARIABLE _testOut
        )
        if (${IS_CMAKE_SOURCE_DIR_A_GIT_DIRECTORY})
            # Get the git branch name
            execute_process(
                COMMAND git rev-parse --abbrev-ref HEAD
                WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
                OUTPUT_VARIABLE GIT_BRANCH
                OUTPUT_STRIP_TRAILING_WHITESPACE
            )

            # Get the latest abbreviated commit hash of the working branch
            execute_process(
                COMMAND git log -1 --format=%H
                WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
                OUTPUT_VARIABLE GIT_COMMIT_HASH
                OUTPUT_STRIP_TRAILING_WHITESPACE
            )
            message("Git commit hash ${GIT_COMMIT_HASH}")

            # Get the version tag from git
            execute_process(
                COMMAND git for-each-ref refs/tags --sort=-taggerdate --count=1
                WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
                OUTPUT_VARIABLE GIT_OBENGINE_VERSION_UNFORMATTED
                OUTPUT_STRIP_TRAILING_WHITESPACE
            )
            string(REGEX MATCH "v(.+)\.(.+)\.(.+)$" GIT_OBENGINE_VERSION "${GIT_OBENGINE_VERSION_UNFORMATTED}")

            set_git_version("${GIT_BRANCH}" "${GIT_COMMIT_HASH}" "${GIT_OBENGINE_VERSION}")
            message("ÖbEngine Git version : ${OBENGINE_GIT_BRANCH}:${OBENGINE_GIT_COMMIT_HASH}")
            message("ÖbEngine version : ${OBENGINE_VERSION}")
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