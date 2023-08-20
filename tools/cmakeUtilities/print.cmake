########################################
# File:     print.cmake
# Created:  8/19/2023
# By:       Kaleb C
########################################

cmake_minimum_required(VERSION 3.22)

########################################
# Colors
########################################

if(DEFINED COLORS_OFF OR WIN32)
    set(COLOR_RESET         "")
    set(COLOR_BOLD          "")
    set(COLOR_COLOR_RED     "")
    set(COLOR_GREEN         "")
    set(COLOR_YELLOW        "")
    set(COLOR_BLUE          "")
    set(COLOR_MAGENTA       "")
    set(COLOR_CYAN          "")
    set(COLOR_WHITE         "")
    set(COLOR_BOLD_RED      "")
    set(COLOR_BOLD_GREEN    "")
    set(COLOR_BOLD_YELLOW   "")
    set(COLOR_BOLD_BLUE     "")
    set(COLOR_BOLD_MAGENTA  "")
    set(COLOR_BOLD_CYAN     "")
    set(COLOR_BOLD_WHITE    "")
else()
    string(ASCII 27 Esc)
    set(COLOR_RESET         "${Esc}[m")
    set(COLOR_BOLD          "${Esc}[1m")
    set(COLOR_RED           "${Esc}[31m")
    set(COLOR_GREEN         "${Esc}[32m")
    set(COLOR_YELLOW        "${Esc}[33m")
    set(COLOR_BLUE          "${Esc}[34m")
    set(COLOR_MAGENTA       "${Esc}[35m")
    set(COLOR_CYAN          "${Esc}[36m")
    set(COLOR_WHITE         "${Esc}[37m")
    set(COLOR_BOLD_RED      "${Esc}[1;31m")
    set(COLOR_BOLD_GREEN    "${Esc}[1;32m")
    set(COLOR_BOLD_YELLOW   "${Esc}[1;33m")
    set(COLOR_BOLD_BLUE     "${Esc}[1;34m")
    set(COLOR_BOLD_MAGENTA  "${Esc}[1;35m")
    set(COLOR_BOLD_CYAN     "${Esc}[1;36m")
    set(COLOR_BOLD_WHITE    "${Esc}[1;37m")
endif()

########################################
# Functions
########################################

function(PRINT MSG)
    if(${ARGC} EQUAL 1)
        message(STATUS "${COLOR_BOLD_CYAN}[ CMAKE ] ${MSG}${COLOR_RESET}")
    else()
        message(FATAL_ERROR "[ FATAL ] Bad Print Message!")
    endif()
endfunction()

function(PRINT_WARNING MSG)
    if(${ARGC} EQUAL 1)
        message(STATUS "${COLOR_YELLOW}[ WARN  ] ${MSG}${COLOR_RESET}")
    else()
        message(FATAL_ERROR "[ FATAL ] Bad Print Message!")
    endif()
endfunction()

function(PRINT_ERROR MSG)
    if(${ARGC} EQUAL 1)
        message(STATUS "${COLOR_RED}[ ERROR ] ${MSG}${COLOR_RESET}")
    else()
        message(FATAL_ERROR "[ FATAL ] Bad Print Message!")
    endif()
endfunction()

function(PRINT_FATAL MSG)
    if(${ARGC} EQUAL 1)
        message(FATAL_ERROR "${COLOR_BOLD_RED}[ FATAL ] ${MSG}${COLOR_RESET}")
    else()
        message(FATAL_ERROR "[ FATAL ] Bad Print Message!")
    endif()
endfunction()

########################################