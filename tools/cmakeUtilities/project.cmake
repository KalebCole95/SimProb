########################################
# File:     project.cmake
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
PRINT("      Path:          ${PROJECT_ROOT_PATH}")
PRINT("      Build Skew:    ${BUILD_SKEW}")
PRINT("      Build Type:    ${CMAKE_BUILD_TYPE}")

########################################
# Target Debug & Release
########################################
if(BUILD_SKEW MATCHES "linux")

    # Set Component Names
    set(_COMPONENT_NAMES "")
    list(APPEND _COMPONENT_NAMES "${_PROJECT_COMPONENTS}")
    list(REMOVE_DUPLICATES _COMPONENT_NAMES)

    # Set Component Libraries (use the tail of the path as the component/library name)
    set(_COMPONENT_LIBRARIES "")
    foreach(_COMPONENT ${_COMPONENT_NAMES})
       set (myPath ${_COMPONENT})
       cmake_path(GET myPath FILENAME compName)
       list(APPEND _COMPONENT_LIBRARIES "${compName}_${BUILD_SKEW}_${CMAKE_BUILD_TYPE}")
    endforeach()
    list(REMOVE_DUPLICATES _COMPONENT_LIBRARIES)

    # Set Precompiled Libraries
    set(_PRECOMPILED_LIBRARIES "")
    list(APPEND _PRECOMPILED_LIBRARIES ${_PROJECT_LIBRARIES})
    list(REMOVE_DUPLICATES _PRECOMPILED_LIBRARIES)

    # Set Compile & Link Options
    add_compile_options("${_PROJECT_COMPILE_OPTIONS}")
    add_link_options("${_PROJECT_LINK_OPTIONS}")

    # Set Sources
    set(_SOURCES "")
    list(APPEND _SOURCES "${_PROJECT_SOURCES}")
    list(REMOVE_DUPLICATES _SOURCES)

    # Set Include Directories
    set(_INCLUDE_DIRECTORIES "")
    foreach(_DIR ${_PROJECT_INCLUDE_DIRECTORIES})
        list(APPEND _INCLUDE_DIRECTORIES "${PROJECT_ROOT_PATH}/${_DIR}")
    endforeach()
    list(REMOVE_DUPLICATES _INCLUDE_DIRECTORIES)

    # Call To Components
    foreach(_COMP ${_COMPONENT_NAMES})
        add_subdirectory("${PROJECT_ROOT_PATH}/${_COMP}" "${PROJECT_ROOT_PATH}/${_COMP}/build/${BUILD_SKEW}/${CMAKE_BUILD_TYPE}")
    endforeach()

    # Add Target
    include_directories(${_INCLUDE_DIRECTORIES})
    add_executable(${PROJECT_NAME} ${_SOURCES})
    target_link_libraries(${PROJECT_NAME} PUBLIC ${_COMPONENT_LIBRARIES}) 

    return()

########################################
# Unittest & Stub
########################################
elseif(BUILD_SKEW MATCHES "unittest" OR
    BUILD_SKEW MATCHES "stub")
    PRINT_FATAL("Cannot build skew '${BUILD_SKEW}' from the project level")
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
