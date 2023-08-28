########################################
# File:     SimProb CMakeLists.txt
# Created:  8/25/2023
# By:       Kaleb C
########################################

cmake_minimum_required(VERSION 3.22)

########################################

include("${CMAKE_CURRENT_LIST_DIR}/defaults.cmake")

########################################
# Project Name
########################################

set(_PROJECT_NAME   "SimProb")

########################################
# Project Files
########################################

set(_PROJECT_SOURCES                "main.cpp")
set(_PROJECT_INCLUDE_DIRECTORIES    ".")
set(_PROJECT_COMPONENTS             "aircrafts"
                                    "chargers"
                                    "units"
                                    "statistics")
set(_PROJECT_LIBRARIES              "")

########################################
# Configuration
########################################

project("${_PROJECT_NAME}_${BUILD_SKEW}_${CMAKE_BUILD_TYPE}")
include("${CMAKE_TOOLS_PATH}/project.cmake")

########################################
