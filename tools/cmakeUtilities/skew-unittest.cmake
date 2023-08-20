########################################
# File:     skew-unittest.cmake
# Created:  8/19/2023
# By:       Kaleb C
########################################

cmake_minimum_required(VERSION 3.22)

########################################
# Sources
########################################
set(_SOURCES "")
list(APPEND _SOURCES ${_TARGET_SOURCES})
list(APPEND _SOURCES ${_TEST_SOURCES})
list(REMOVE_DUPLICATES _SOURCES)

########################################
# Include Directories
########################################
set(_PUBLIC_INCLUDE_DIRECTORIES "")
list(APPEND _PUBLIC_INCLUDE_DIRECTORIES "${_COMPONENT_ROOT_PATH}")
list(APPEND _PUBLIC_INCLUDE_DIRECTORIES "${PROJECT_ROOT_PATH}")
list(REMOVE_DUPLICATES _PUBLIC_INCLUDE_DIRECTORIES)

set(_PRIVATE_INCLUDE_DIRECTORIES "")
list(APPEND _PRIVATE_INCLUDE_DIRECTORIES "${_COMPONENT_ROOT_PATH}/source")
list(APPEND _PRIVATE_INCLUDE_DIRECTORIES "${_COMPONENT_ROOT_PATH}/test")
list(REMOVE_DUPLICATES _PRIVATE_INCLUDE_DIRECTORIES)

########################################
# Dependencies
########################################
set(BUILD_SKEW "stub")

set(_DEPENDENCY_COMPONENT_NAMES "")
list(APPEND _DEPENDENCY_COMPONENT_NAMES ${_COMPONENT_DEPENDENCIES})
list(REMOVE_DUPLICATES _DEPENDENCY_COMPONENT_NAMES)

set(_DEPENDENCY_LIBRARY_NAMES "")
foreach(_DEP ${_DEPENDENCY_COMPONENT_NAMES})
    add_subdirectory("${PROJECT_ROOT_PATH}/${_DEP}" "${PROJECT_ROOT_PATH}/${_DEP}/build/${BUILD_SKEW}/${CMAKE_BUILD_TYPE}/")
    list(APPEND _DEPENDENCY_LIBRARY_NAMES "${_DEP}_${BUILD_SKEW}_${CMAKE_BUILD_TYPE}")
endforeach()
list(REMOVE_DUPLICATES _DEPENDENCY_LIBRARY_NAMES)

set(BUILD_SKEW "unittest")

########################################
# Testing
########################################
add_subdirectory("/usr/src/gtest" "/usr/src/gtest/build/stub/${CMAKE_BUILD_TYPE}")
enable_testing()

########################################
# Add Executable
########################################
include_directories(${_PUBLIC_INCLUDE_DIRECTORIES} ${_PRIVATE_INCLUDE_DIRECTORIES})
add_executable(${PROJECT_NAME} ${_SOURCES})
target_link_libraries(${PROJECT_NAME} PUBLIC ${_DEPENDENCY_LIBRARY_NAMES} "gtest" "gtest_main")

########################################
# Google Test
########################################
include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})

########################################