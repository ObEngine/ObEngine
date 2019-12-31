
function (copy_required_dlls TARGET)
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
    endif()
endfunction()