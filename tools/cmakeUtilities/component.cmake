########################################
# File:     component.cmake
# Created:  8/19/2023
# By:       Kaleb C
########################################
cmake_minimum_required(VERSION 3.22)

########################################
# Get Compilation Flags
########################################
include("${CMAKE_TOOLS_PATH}/compilationFlags.cmake")

########################################
# Status Message
########################################
PRINT("${PROJECT_NAME} (${BUILD_VERSION})")
PRINT("      Path:          ${_COMPONENT_ROOT_PATH}")
PRINT("      Build Skew:    ${BUILD_SKEW}")
PRINT("      Build Type:    ${CMAKE_BUILD_TYPE}")

########################################
# Unittest
########################################
if(BUILD_SKEW MATCHES "unittest")
    include("${CMAKE_TOOLS_PATH}/skew-unittest.cmake")
    return()

########################################
# Test Stub
########################################
elseif(BUILD_SKEW MATCHES "stub")
    include("${CMAKE_TOOLS_PATH}/skew-stub.cmake")
    return()

########################################
# Target Debug & Release
########################################
elseif(BUILD_SKEW MATCHES "linux")
    include("${CMAKE_TOOLS_PATH}/skew-target.cmake")
    return()

########################################
# Undefined Build Type
########################################
elseif(NOT DEFINED CMAKE_BUILD_TYPE)
    PRINT_FATAL("'CMAKE_BUILD_TYPE' was not set")
    return()
else()
    PRINT_FATAL("Could not recognize build type '${CMAKE_BUILD_TYPE}'")
    return()
endif()

########################################
