########################################
# File:     skew-target.cmake
# Created:  8/19/2023
# By:       Kaleb C
########################################
cmake_minimum_required(VERSION 3.22)

########################################
# Sources
########################################
set(_SOURCES "")
list(APPEND _SOURCES ${_TARGET_SOURCES})
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
list(REMOVE_DUPLICATES _PRIVATE_INCLUDE_DIRECTORIES)

########################################
# Dependencies
########################################
set(_DEPENDENCY_COMPONENT_NAMES "")
list(APPEND _DEPENDENCY_COMPONENT_NAMES ${_COMPONENT_DEPENDENCIES})
list(REMOVE_DUPLICATES _DEPENDENCY_COMPONENT_NAMES)

set(_DEPENDENCY_LIBRARY_NAMES "")
foreach(_DEP ${_DEPENDENCY_COMPONENT_NAMES})
    list(APPEND _DEPENDENCY_LIBRARY_NAMES "${_DEP}_${BUILD_SKEW}_${CMAKE_BUILD_TYPE}")
endforeach()
list(REMOVE_DUPLICATES _DEPENDENCY_LIBRARY_NAMES)

########################################
# Add Library
########################################
if(_SOURCES)
    PRINT("      Library Type:  STATIC")
    include_directories(${_PUBLIC_INCLUDE_DIRECTORIES} ${_PRIVATE_INCLUDE_DIRECTORIES})
    add_library(${PROJECT_NAME} STATIC ${_SOURCES})
    target_sources(${PROJECT_NAME} PUBLIC ${_SOURCES})
    target_link_libraries(${PROJECT_NAME} PRIVATE ${_DEPENDENCY_LIBRARY_NAMES})
    target_include_directories(${PROJECT_NAME}
            PUBLIC ${_PUBLIC_INCLUDE_DIRECTORIES}
            PRIVATE ${_PRIVATE_INCLUDE_DIRECTORIES})
else()
    PRINT("      Library Type:  INTERFACE")
    include_directories(${_PUBLIC_INCLUDE_DIRECTORIES} ${_PRIVATE_INCLUDE_DIRECTORIES})
    add_library(${PROJECT_NAME} INTERFACE ${_SOURCES})
    target_link_libraries(${PROJECT_NAME} PRIVATE ${_DEPENDENCY_LIBRARY_NAMES})
    target_include_directories(${PROJECT_NAME} INTERFACE ${_PUBLIC_INCLUDE_DIRECTORIES} ${_PRIVATE_INCLUDE_DIRECTORIES})
endif()

########################################
