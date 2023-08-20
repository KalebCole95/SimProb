########################################
# File:     compilationFlags.cmake
# Created:  8/19/2023
# By:       Kaleb C
########################################

cmake_minimum_required(VERSION 3.22)

########################################

include("${CMAKE_CURRENT_LIST_DIR}/../../software/defaults.cmake")

########################################
# Add Precompiler Definitions
########################################

string(TOUPPER CMAKE_BUILD_TYPE _CMAKE_BUILD_TYPE_DEFINITION)
add_compile_definitions("${_CMAKE_BUILD_TYPE_DEFINITION}")
string(TOUPPER BUILD_SKEW _BUILD_SKEW_DEFINITION)
add_compile_definitions("${_BUILD_SKEW_DEFINITION}")

########################################
# Common
########################################
set(CMAKE_CXX_FLAGS         "${CMAKE_CXX_FLAGS}         -Wall -std=c++17")
set(CMAKE_C_FLAGS           "${CMAKE_C_FLAGS}           -Wall")
set(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS}  ")

########################################
# generic_linux skew
########################################
if(BUILD_SKEW MATCHES "linux")
    if(CMAKE_BUILD_TYPE MATCHES "debug")
        set(CMAKE_CXX_FLAGS         "${CMAKE_CXX_FLAGS}         -g -DDEBUG")
        set(CMAKE_C_FLAGS           "${CMAKE_C_FLAGS}           -g -DDEBUG")
        set(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS}  ")
    else()
        set(CMAKE_CXX_FLAGS         "${CMAKE_CXX_FLAGS}         ")
        set(CMAKE_C_FLAGS           "${CMAKE_C_FLAGS}           ")
        set(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS}  ")
    endif()
    return()

########################################
# unittest skew
########################################
elseif(BUILD_SKEW MATCHES "unittest")
    set(CMAKE_CXX_FLAGS         "${CMAKE_CXX_FLAGS}        -g -DDEBUG -fprofile-arcs -ftest-coverage")
    set(CMAKE_C_FLAGS           "${CMAKE_C_FLAGS}          -g -DDEBUG -fprofile-arcs -ftest-coverage")
    set(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} -lgcov")
    return()

########################################
# stub skew
########################################
elseif(BUILD_SKEW MATCHES "stub")
    set(CMAKE_CXX_FLAGS         "${CMAKE_CXX_FLAGS}        -g -DDEBUG -fprofile-arcs -ftest-coverage -std=c++17")
    set(CMAKE_C_FLAGS           "${CMAKE_C_FLAGS}          -g -DDEBUG -fprofile-arcs -ftest-coverage")
    set(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} -lgcov")
    return()

########################################
# Undefined Build Skew
########################################
elseif(NOT DEFINED BUILD_SKEW)
    PRINT_FATAL("'BUILD_SKEW' was not set")
    return()
else()
    PRINT_FATAL("Could not recognize build skew '${BUILD_SKEW}'")
    return()
endif()

########################################
