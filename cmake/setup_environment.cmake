
function (copy_required_dlls TARGET)
    # SFML Graphics DLL
    get_target_property(dlls-sfml-graphics-dbg sfml-graphics IMPORTED_LOCATION_DEBUG)
    get_target_property(dlls-sfml-graphics-rel sfml-graphics IMPORTED_LOCATION_RELEASE)
    get_target_property(dlls-sfml-graphics-msr sfml-graphics IMPORTED_LOCATION_MINSIZEREL)
    get_target_property(dlls-sfml-graphics-rwd sfml-graphics IMPORTED_LOCATION_RELWITHDEBINFO)
    # SFML System DLL
    get_target_property(dlls-sfml-system-dbg sfml-system IMPORTED_LOCATION_DEBUG)
    get_target_property(dlls-sfml-system-rel sfml-system IMPORTED_LOCATION_RELEASE)
    get_target_property(dlls-sfml-system-msr sfml-system IMPORTED_LOCATION_MINSIZEREL)
    get_target_property(dlls-sfml-system-rwd sfml-system IMPORTED_LOCATION_RELWITHDEBINFO)
    # SFML Window DLL
    get_target_property(dlls-sfml-window-dbg sfml-window IMPORTED_LOCATION_DEBUG)
    get_target_property(dlls-sfml-window-rel sfml-window IMPORTED_LOCATION_RELEASE)
    get_target_property(dlls-sfml-window-msr sfml-window IMPORTED_LOCATION_MINSIZEREL)
    get_target_property(dlls-sfml-window-rwd sfml-window IMPORTED_LOCATION_RELWITHDEBINFO)

    if (WIN32)
        add_custom_command(TARGET ${TARGET} POST_BUILD
            COMMAND ("${CMAKE_COMMAND}" -E copy_if_different
                $<$<CONFIG:Debug>:"${dlls-sfml-graphics-dbg}">
                $<$<CONFIG:Release>:"${dlls-sfml-graphics-rel}">
                $<$<CONFIG:MinSizeRel>:"${dlls-sfml-graphics-msr}">
                $<$<CONFIG:RelWithDebInfo>:"${dlls-sfml-graphics-rwd}">
                $<TARGET_FILE_DIR:${TARGET}>
            )
            COMMAND ("${CMAKE_COMMAND}" -E copy_if_different
                $<$<CONFIG:Debug>:"${dlls-sfml-system-dbg}">
                $<$<CONFIG:Release>:"${dlls-sfml-system-rel}">
                $<$<CONFIG:MinSizeRel>:"${dlls-sfml-system-msr}">
                $<$<CONFIG:RelWithDebInfo>:"${dlls-sfml-system-rwd}">
                $<TARGET_FILE_DIR:${TARGET}>
            )
            COMMAND ("${CMAKE_COMMAND}" -E copy_if_different
                $<$<CONFIG:Debug>:"${dlls-sfml-window-dbg}">
                $<$<CONFIG:Release>:"${dlls-sfml-window-rel}">
                $<$<CONFIG:MinSizeRel>:"${dlls-sfml-window-msr}">
                $<$<CONFIG:RelWithDebInfo>:"${dlls-sfml-window-rwd}">
                $<TARGET_FILE_DIR:${TARGET}>
            )
        )
    endif()
endfunction()