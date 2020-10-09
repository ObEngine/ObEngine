function(obe_check_vcpkg var)
    option(USE_VCPKG "Use vcpkg to handle some of the dependencies" OFF)
    if(DEFINED ENV{VCPKG_ROOT} AND NOT DEFINED CMAKE_TOOLCHAIN_FILE
        OR USE_VCPKG)
        set(${var} ON PARENT_SCOPE)
        set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake"
            CACHE STRING "")
    endif()

    if(${var})
        if(NOT DEFINED ENV{VCPKG_FEATURE_FLAGS})
        message(FATAL_ERROR
            "Using vcpkg to build ObEngine without defining ${VCPKG_FEATURE_FLAGS} to be \"manifests\"!! Aborting...") # manifests are required because of vcpkg.json
        endif()

        if(NOT DEFINED ENV{VCPKG_DEFAULT_TRIPLET})
            message(FATAL_ERROR
                "Using vcpkg to build ObEngine without defining ${VCPKG_DEFAULT_TRIPLET}!! Aborting...")
        endif()
    endif()
endfunction()