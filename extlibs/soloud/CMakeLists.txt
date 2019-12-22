project(Soloud)

file(GLOB SOLOUD_HEADERS include/soloud/*.h)
file(GLOB_RECURSE SOLOUD_SOURCES
    src/audiosource/*.c src/audiosource/*.cpp
    src/filter/*.cpp
    src/core/*.cpp
)

if (WIN32)
    file(GLOB BACKEND_SOURCES
        src/backend/winmm/soloud_winmm.cpp
    )
elseif(UNIX AND NOT APPLE)
    file(GLOB BACKEND_SOURCES
        src/backend/alsa/soloud_alsa.cpp
    )
elseif(APPLE)
    file(GLOB BACKEND_SOURCES
        src/backend/coreaudio/soloud_coreaudio.cpp
    )
endif()

message("Soloud Backend file : " ${BACKEND_SOURCES})
add_library(Soloud ${SOLOUD_SOURCES} ${BACKEND_SOURCES})

target_include_directories(Soloud
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/soloud>
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 11)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_EXTENSIONS OFF)

if (WIN32)
    target_compile_definitions(Soloud PUBLIC WITH_WINMM=1)
elseif(UNIX AND NOT APPLE)
    target_compile_definitions(Soloud PUBLIC WITH_ALSA=1)
    find_package(ALSA REQUIRED)
    if (ALSA_FOUND)
        target_include_directories(Soloud PUBLIC ${ALSA_INCLUDE_DIRS})
        target_link_libraries (Soloud ${ALSA_LIBRARIES})
    endif()
    set(THREADS_PREFER_PTHREAD_FLAG ON)
    find_package(Threads REQUIRED)
    target_link_libraries(Soloud Threads::Threads)
elseif(APPLE)
    target_compile_definitions(Soloud PUBLIC WITH_COREAUDIO=1)
    target_link_libraries(Soloud "-framework CoreFoundation")
    target_link_libraries(Soloud "-framework CoreAudio")
    target_link_libraries(Soloud "-framework AudioToolbox")
endif()