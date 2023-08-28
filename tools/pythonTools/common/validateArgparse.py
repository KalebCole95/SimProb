################################################################################
# File:     validateArgparse.py
# Created:  8/28/2023
# By:       Kaleb C
################################################################################

# Standard Libraries
import os
import sys

# Common Libraries
from common.prettyPrint import PrettyPrint, Verbosity, COLORS

################################################################################

def validateVerbosity(verbosity: int) -> Verbosity:
    match verbosity:
        case "0":
            return Verbosity.LOW
        case "1":
            return Verbosity.MEDIUM
        case "2":
            return Verbosity.HIGH
        case _:
            return Verbosity.LOW

########################################

def validateFilePath(filePath: str) -> str:
    filePath = os.path.abspath(filePath)

    if os.path.exists(filePath):
        return filePath
    else:
        PrettyPrint().fatal("Error: File at '{Path}' does not exist".format(Path = filePath))
        sys.exit(1)

########################################

def validateDirectoryPath(directoryPath: str) -> str:
    directoryPath = os.path.abspath(directoryPath)
    if os.path.exists(directoryPath):
        return directoryPath
    else:
        PrettyPrint().fatal("Path not found: {Path}".format(Path = directoryPath, **COLORS))
        sys.exit(1)

########################################

def validateOrCreateDirectoryPath(directoryPath: str) -> str:
    directoryPath = os.path.abspath(directoryPath)

    if os.path.exists(directoryPath):
        return directoryPath
    else:
        PrettyPrint().warning("Creating Path: {Path}".format(Path = directoryPath, **COLORS))
        os.mkdir(directoryPath)
        return directoryPath

################################################################################
