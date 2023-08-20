########################################
# File:     defaults.cmake
# Created:  8/19/2023
# By:       Kaleb C
########################################

cmake_minimum_required(VERSION 3.22)

########################################
# Set Defaults
########################################

# Project Root Path
if(NOT DEFINED PROJECT_ROOT_PATH OR PROJECT_ROOT_PATH STREQUAL "")
    set(PROJECT_ROOT_PATH "${CMAKE_CURRENT_LIST_DIR}")
endif()

# CMake Tools Path
if(NOT DEFINED CMAKE_TOOLS_PATH OR CMAKE_TOOLS_PATH STREQUAL "")
    set(CMAKE_TOOLS_PATH "${PROJECT_ROOT_PATH}/../tools/cmakeUtilities")
endif()

# Call to print.cmake to setup print calls
include("${CMAKE_TOOLS_PATH}/print.cmake")

# Build Version
if(NOT DEFINED BUILD_VERSION OR BUILD_VERSION STREQUAL "")
    PRINT_WARNING("BUILD_VERSION not set, defaulting to 'Y--W--B--'")
    set(BUILD_VERSION "Y--W--B--")
endif()

# Build Skew
if((NOT DEFINED BUILD_SKEW OR BUILD_SKEW STREQUAL "")
    AND NOT BUILD_SKEW MATCHES "linux"
    AND NOT BUILD_SKEW MATCHES "unittest"
    AND NOT BUILD_SKEW MATCHES "stub")
    PRINT_FATAL("BUILD_SKEW '${BUILD_SKEW}' not recognized, exiting...")
endif()

if(BUILD_SKEW MATCHES "unittest" OR BUILD_SKEW MATCHES "stub")
    set(CMAKE_BUILD_TYPE "debug")
endif()

# CMake Build Type
if((NOT DEFINED CMAKE_BUILD_TYPE OR CMAKE_BUILD_TYPE STREQUAL "")
    AND NOT CMAKE_BUILD_TYPE MATCHES "debug"
    AND NOT CMAKE_BUILD_TYPE MATCHES "release")
    PRINT_FATAL("CMAKE_BUILD_TYPE '${CMAKE_BUILD_TYPE}' not recognized, exiting...")
endif()

########################################