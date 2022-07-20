cmake_minimum_required(VERSION 3.0)

# C++17 Standards
set(CMAKE_CXX_STANDARD 17)

# Static build option
option(AE_STATIC OFF)
# Build engine as a static library on windows
if (WIN32)
    set(AE_STATIC OFF)
endif()

# Detect target build architecture
include(${CMAKE_SOURCE_DIR}/CMake/TargetArch.cmake)
target_architecture(TARGET_ARCH)
message("-- Target Architecture: ${TARGET_ARCH}")

# External libraries
set(LIB_DIR ${CMAKE_SOURCE_DIR}/Libs)
include(${CMAKE_SOURCE_DIR}/CMake/Libs.cmake)

# AEngine project
project(AEngine VERSION 1.0)
set(PROJECT_DIR ${CMAKE_SOURCE_DIR}/AEngine)
include(${CMAKE_SOURCE_DIR}/CMake/${PROJECT_NAME}.cmake)

# AEditor project (only for windows)
if (WIN32)
    project(AEditor VERSION 1.0)
    set(PROJECT_DIR ${CMAKE_SOURCE_DIR}/AEditor)
    include(${CMAKE_SOURCE_DIR}/CMake/${PROJECT_NAME}.cmake)
endif()

# Test Application project
project(TestApp VERSION 1.0)
set(PROJECT_DIR ${CMAKE_SOURCE_DIR}/TestApp)
include(${CMAKE_SOURCE_DIR}/CMake/${PROJECT_NAME}.cmake)
