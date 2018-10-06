cmake_minimum_required(VERSION 3.6)

project(ObEngineAndroid)

if (NOT DEFINED ANDROID_FROMX86)
  set(ANDROID_FROMX86 OFF CACHE BOOL "Android From x86 ?")
endif()

if (NOT ANDROID_FROMX86)
  set(${CMAKE_C_FLAGS}, "${CMAKE_C_FLAGS}")
  add_library(native_app_glue STATIC ${ANDROID_NDK}/sources/android/native_app_glue/android_native_app_glue.c)
endif()

file(GLOB_RECURSE OBEDROID_HEADERS "${ObEngine_SOURCE_DIR}/include/Android/*.hpp")
file(GLOB_RECURSE OBEDROID_SOURCES "${ObEngine_SOURCE_DIR}/src/Android/*.cpp")

if (ANDROID_FROMX86)
  add_executable(ObEngineAndroid ${OBEDROID_HEADERS} ${OBEDROID_SOURCES})
  target_compile_definitions(ObEngineAndroid PRIVATE ANDROID_FROMX86)
else()
  add_library(ObEngineAndroid SHARED ${OBEDROID_HEADERS} ${OBEDROID_SOURCES})
endif()


target_include_directories(ObEngineAndroid
  PRIVATE
    $<BUILD_INTERFACE:${ObEngine_SOURCE_DIR}/include/Android>
    ${ANDROID_NDK}/sources/android/native_app_glue
)

set(CMAKE_SHARED_LINKER_FLAGS
"${CMAKE_SHARED_LINKER_FLAGS} -u ANativeActivity_onCreate")

target_link_libraries(ObEngineAndroid ObEngineCore)
target_link_libraries(ObEngineAndroid fmt)
target_link_libraries(ObEngineAndroid spdlog)
if (NOT ANDROID_FROMX86)
  target_link_libraries(ObEngineAndroid android)
  target_link_libraries(ObEngineAndroid log)
  target_link_libraries(ObEngineAndroid native_app_glue)
endif()

#target_link_libraries(ObEngineAndroid lua)
#target_link_libraries(ObEngineAndroid sfe)
#target_link_libraries(ObEngineAndroid vili)
#target_link_libraries(ObEngineAndroid dynamicLinker)

#if(SFML_FOUND)
  #target_link_libraries(ObEngineAndroid sfml-window)
#endif()

#if (UNIX)
#    target_link_libraries(ObEngineAndroid ${CMAKE_DL_LIBS})
#endif()

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_EXTENSIONS OFF)

if (MSVC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++latest")
endif (MSVC)