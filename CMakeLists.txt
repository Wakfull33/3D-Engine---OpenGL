cmake_minimum_required(VERSION 3.25)
project(OpenGL VERSION 0.1.0 LANGUAGES C CXX)

# Define build paths for different build types
set(BUILD_DIR ${CMAKE_CURRENT_SOURCE_DIR}/build)
set(BIN_DIR ${BUILD_DIR}/bin)

# Path for build type-specific files
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(BUILD_TYPE_DIR "Debug")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
else()
    set(BUILD_TYPE_DIR "Release")
endif()

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(TEMP_DIR ${BUILD_DIR}/temp)

# Create directories if they don't exist
file(MAKE_DIRECTORY ${TEMP_DIR})
file(MAKE_DIRECTORY ${BIN_DIR})

# Source files location
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/OGL3D/source)

# List of source files
file(GLOB SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/Game/main.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Game/MyGame.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Game/MyPlayer.cpp"

    "${SOURCE_DIR}/OGL3D/Game/Win32/CWin32Game.cpp"
    "${SOURCE_DIR}/OGL3D/Game/OGame.cpp"

    "${SOURCE_DIR}/OGL3D/Graphics/Win32/CWin32GraphicsEngine.cpp"
    "${SOURCE_DIR}/OGL3D/Graphics/*.cpp"

    "${SOURCE_DIR}/OGL3D/Window/CWin32Window.cpp"

    "${SOURCE_DIR}/OGL3D/Entity/*.cpp"

    "${CMAKE_CURRENT_SOURCE_DIR}/OGL3D/vendor/glad/src/glad_wgl.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/OGL3D/vendor/glad/src/glad.c"
)

# Add executable
add_executable(${PROJECT_NAME} ${SOURCES})

find_package(OpenGL REQUIRED)

# Set include directories
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/OGL3D/include)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/Game)
target_include_directories(${PROJECT_NAME} SYSTEM PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/OGL3D/vendor/glad/include)

target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES})

# message(CMAKE_CURRENT_SOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}")
# message(SOURCE_DIR="${SOURCE_DIR}")

# Copy Media and Shaders
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/Assets
    ${CMAKE_BINARY_DIR}/Debug/Assets
)