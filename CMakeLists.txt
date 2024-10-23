cmake_minimum_required(VERSION 3.19)

# Make sure to init vcpkg correctly before this
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake)
project(hookline)

#=======================================================#
# Compiling
#=======================================================#

# Enforce C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Compile commands for clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Source dir
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Add source files
file(GLOB_RECURSE SOURCES
    ${SOURCE_DIR}/*.cpp
    ${SOURCE_DIR}/*.hpp)

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Compiler flags for Clang
target_compile_options(${PROJECT_NAME} PRIVATE
    # Debug vs. Release compiler options
    # $<$<CONFIG:Debug>:-g>
    $<$<CONFIG:Release>:-O3>
    # Always on compiler options
    -Wall
    -Wextra
    -Werror
    # -Wpedantic -fsanitize=address -fsanitize=undefined
)


#=======================================================#
# Libraries 
#=======================================================#
find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)
find_package(PNG REQUIRED)
find_package(SDL2 REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE
    GLEW::GLEW
    OpenGL::GL
    OpenGL::GLU
    PNG::PNG
    SDL2::SDL2
)

#=======================================================#
# Formatting 
#=======================================================#
add_custom_target(format
    COMMAND clang-format -i ${SOURCES})
