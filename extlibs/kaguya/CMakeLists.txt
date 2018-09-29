project(kaguya)

file(GLOB KAGUYA_HEADERS include/kaguya/*.hpp include/kaguya/detail/*.hpp)

add_library(kaguya INTERFACE)

target_link_libraries(kaguya INTERFACE lua)

target_include_directories(kaguya
    INTERFACE
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)
