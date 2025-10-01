cmake_minimum_required(VERSION 3.19)

project(ArchimedesTemplate)

set(CMAKE_CXX_STANDARD 23)

# MSVC specific behavior
include("cmake/msvc.cmake")

# OS handling
include("cmake/os.cmake")

# Build mode handling
include("cmake/build_mode.cmake")

# Conan handling
include("cmake/conan.cmake")

# Ninja fixes
include("cmake/ninja_fix.cmake")

# #defines
include("cmake/defines.cmake")

# Launch functions
include("cmake/launch.cmake")

add_executable(test "${PROJECT_SOURCE_DIR}/test.cpp")
target_link_libraries(test PRIVATE archimedes::archimedes)
target_include_directories(test PRIVATE ${CMAKE_INCLUDE_PATH})

LaunchAddTarget(test)

LaunchMake()

#target_include_directories(test archimedes_INCLUDE_DIRS)