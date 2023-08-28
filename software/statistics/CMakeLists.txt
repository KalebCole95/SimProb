########################################
# File:     statistics CMakeLists.txt
# Created:  8/25/2023
# By:       Kaleb C
########################################
cmake_minimum_required(VERSION 3.22)

########################################
include("${CMAKE_CURRENT_LIST_DIR}/../defaults.cmake")

########################################
# Component Name
########################################
set(_COMPONENT_NAME "statistics")

########################################
# Target Files
########################################
set(_TARGET_SOURCES "")

########################################
# Dependencies
########################################
set(_COMPONENT_DEPENDENCIES "aircrafts"
                            "units"
                            "chargers")
set(_LIBRARY_DEPENDENCIES   "")

########################################
# Unittest Files
########################################
set(_TEST_SOURCES "test/stats.test.cpp")

########################################
# Stub Files
########################################
set(_STUB_SOURCES "")

########################################
# Configuration
########################################
set(_COMPONENT_ROOT_PATH "${CMAKE_CURRENT_LIST_DIR}")

project("${_COMPONENT_NAME}_${BUILD_SKEW}_${CMAKE_BUILD_TYPE}")
include("${CMAKE_TOOLS_PATH}/component.cmake")

########################################
