########################################
# File:     example CMakeLists.txt
# Created:  8/19/2023
# By:       Kaleb C
########################################
cmake_minimum_required(VERSION 3.22)

########################################
include("${CMAKE_CURRENT_LIST_DIR}/../defaults.cmake")

########################################
# Component Name
########################################
set(_COMPONENT_NAME "example")

########################################
# Target Files
########################################
set(_TARGET_SOURCES "source/example.cpp")

########################################
# Dependencies
########################################
set(_COMPONENT_DEPENDENCIES "")
set(_LIBRARY_DEPENDENCIES   "")

########################################
# Unittest Files
########################################
set(_TEST_SOURCES "test/example.test.cpp")

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
