project(ObEngineTests)

file(GLOB_RECURSE OBT_HEADERS CONFIGURE_DEPENDS src/*.hpp)
file(GLOB_RECURSE OBT_SOURCES CONFIGURE_DEPENDS src/*.cpp)

add_executable(ObEngineTests ${OBT_HEADERS} ${OBT_SOURCES})

target_include_directories(ObEngineTests
  PRIVATE
    $<BUILD_INTERFACE:${OPENGL_INCLUDE_DIR}>
)

target_link_libraries(ObEngineTests ObEngineCore)
target_link_libraries(ObEngineTests catch)
target_link_libraries(ObEngineTests sfml-window)

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_EXTENSIONS OFF)