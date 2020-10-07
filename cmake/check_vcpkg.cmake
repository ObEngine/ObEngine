function(obe_check_vcpkg)
    option(USE_VCPKG "Use vcpkg to handle some of the dependencies" OFF)
    if(DEFINED ENV{VCPKG_ROOT} AND NOT DEFINED CMAKE_TOOLCHAIN_FILE
        OR USE_VCPKG)
        set(OBE_USE_VCPKG ON)
        set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake"
            CACHE STRING "")
    endif()

    if(OBE_USE_VCPKG)
        if(NOT DEFINED ENV{VCPKG_FEATURE_FLAGS})
            set(ENV{VCPKG_FEATURE_FLAGS} "manifests") # manifests are required because of vcpkg.json
        endif()
            
        if(NOT DEFINED ENV{VCPKG_DEFAULT_TRIPLET})
            message(FATAL_ERROR
                "Using vcpkg to build ObEngine without defining ${VCPKG_DEFAULT_TRIPLET}!! Aborting...")
        endif()
    endif()
endfunction()