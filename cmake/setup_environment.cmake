
function (copy_required_dlls TARGET)
    get_target_property(dlls-sfml-audio-dbg sfml-audio IMPORTED_LOCATION_DEBUG)
    get_target_property(dlls-sfml-audio-rel sfml-audio IMPORTED_LOCATION_RELEASE)
    get_target_property(dlls-sfml-graphics-dbg sfml-graphics IMPORTED_LOCATION_DEBUG)
    get_target_property(dlls-sfml-graphics-rel sfml-graphics IMPORTED_LOCATION_RELEASE)
    get_target_property(dlls-sfml-network-dbg sfml-network IMPORTED_LOCATION_DEBUG)
    get_target_property(dlls-sfml-network-rel sfml-network IMPORTED_LOCATION_RELEASE)
    get_target_property(dlls-sfml-system-dbg sfml-system IMPORTED_LOCATION_DEBUG)
    get_target_property(dlls-sfml-system-rel sfml-system IMPORTED_LOCATION_RELEASE)
    get_target_property(dlls-sfml-window-dbg sfml-window IMPORTED_LOCATION_DEBUG)
    get_target_property(dlls-sfml-window-rel sfml-window IMPORTED_LOCATION_RELEASE)

    if (WIN32)
        add_custom_command(TARGET ${TARGET} POST_BUILD
            COMMAND ("${CMAKE_COMMAND}" -E copy_if_different
                $<$<CONFIG:Debug>:"${dlls-sfml-audio-dbg}">
                $<$<CONFIG:Release>:"${dlls-sfml-audio-rel}">
                $<TARGET_FILE_DIR:${TARGET}>
            )
            COMMAND ("${CMAKE_COMMAND}" -E copy_if_different
                $<$<CONFIG:Debug>:"${dlls-sfml-graphics-dbg}">
                $<$<CONFIG:Release>:"${dlls-sfml-graphics-rel}">
                $<TARGET_FILE_DIR:${TARGET}>
            )
            COMMAND ("${CMAKE_COMMAND}" -E copy_if_different
                $<$<CONFIG:Debug>:"${dlls-sfml-network-dbg}">
                $<$<CONFIG:Release>:"${dlls-sfml-network-rel}">
                $<TARGET_FILE_DIR:${TARGET}>
            )
            COMMAND ("${CMAKE_COMMAND}" -E copy_if_different
                $<$<CONFIG:Debug>:"${dlls-sfml-system-dbg}">
                $<$<CONFIG:Release>:"${dlls-sfml-system-rel}">
                $<TARGET_FILE_DIR:${TARGET}>
            )
            COMMAND ("${CMAKE_COMMAND}" -E copy_if_different
                $<$<CONFIG:Debug>:"${dlls-sfml-window-dbg}">
                $<$<CONFIG:Release>:"${dlls-sfml-window-rel}">
                $<TARGET_FILE_DIR:${TARGET}>
            )
        )
        get_filename_component(SFML_BACK_DIR ${SFML_DIR} DIRECTORY)
        get_filename_component(SFML_BACK_BACK_DIR ${SFML_BACK_DIR} DIRECTORY)
        get_filename_component(SFML_BACK_BACK_BACK_DIR ${SFML_BACK_BACK_DIR} DIRECTORY)
        find_file(
            OPENAL_DLL
            NAMES "openal32.dll"
            PATHS
                ${SFML_DIR}/bin
                ${SFML_BACK_BACK_BACK_DIR}/bcxx
        )
        if (OPENAL_DLL)
            add_custom_command(
                TARGET ${TARGET} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                        ${OPENAL_DLL}
                        $<TARGET_FILE_DIR:${TARGET}>/openal32.dll
            )
            message("Found OpenAL DLL : ${OPENAL_DLL}")
        else()
            message("OpenAL DLL not found, manual copy might be required")
        endif()
    endif()
endfunction()