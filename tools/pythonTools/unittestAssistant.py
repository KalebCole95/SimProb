#! /usr/bin/python

################################################################################
# File:     unittestAssistant.py
# Created:  8/28/2023
# By:       Kaleb C
################################################################################

# Standard Libraries
import os
import argparse
import subprocess
import enum
import pathlib

# Common Libraries
from common.prettyPrint import PrettyPrint, COLORS
from common import validateArgparse as Validate
from common.command import Command
from common.component import Component, generateComponentDict, getSubsetComponentDict

################################################################################
# Global Variables
################################################################################

CONFIG_DICT = {
    "PrimaryColor": "BrightMagenta",
    "SecondaryColor": "Magenta",
    "Shorthand": "UNIT",
    "FullName": "Unittest Assistant",
    "Header": [  # https://patorjk.com/software/taag/#p=display&c=bash&f=Big&t=%0A%0A
        r"########################################################################################",
        r"#    _    _       _ _   _           _                      _     _              _      #",
        r"#   | |  | |     (_| | | |         | |       /\           (_)   | |            | |     #",
        r"#   | |  | |_ __  _| |_| |_ ___ ___| |_     /  \   ___ ___ _ ___| |_ __ _ _ __ | |_    #",
        r"#   | |  | | '_ \| | __| __/ _ / __| __|   / /\ \ / __/ __| / __| __/ _` | '_ \| __|   #",
        r"#   | |__| | | | | | |_| ||  __\__ | |_   / ____ \\__ \__ | \__ | || (_| | | | | |_    #",
        r"#    \____/|_| |_|_|\__|\__\___|___/\__| /_/    \_|___|___|_|___/\__\__,_|_| |_|\__|   #",
        r"########################################################################################"
    ]
}

################################################################################
# Find Tracefiles
################################################################################

def scanFolderTree(projectRoot):
    subfolders = [f.path for f in os.scandir(projectRoot) if f.is_dir()]
    for folder in list(subfolders):
            subfolders.extend(scanFolderTree(folder))
    return subfolders


def generateTracefileAdd(arguments: dict) -> list:
    tracefileAddList = []
    folderList = scanFolderTree(arguments["coverage_output_root"])
    for folder in folderList:
        fileName = "unittest.info"
        filePath = os.path.join(folder, fileName)
        if os.path.isfile(filePath) and open(filePath, "r").read() != "":
            if (len(tracefileAddList) > 0):
                tracefileAddList.append("-a")
            tracefileAddList.append(filePath)
    return tracefileAddList


################################################################################
# Main
################################################################################

def main(arguments: dict) -> None:
    componentDict = generateComponentDict(arguments["software_root"])

    if(arguments["subset"]):
        componentDict = getSubsetComponentDict(componentDict, arguments["subset"])

    ########################################

    componentCount = len(componentDict)
    componentIndex = 1

    for key, component in componentDict.items():
        generateBuildFiles_CMD = Command(
            "Generate Build Files",
            [
                "cmake",
                "-B",
                "build/unittest/unittest".format(**arguments),
                "-DCMAKE_BUILD_TYPE=unittest".format(**arguments),
                "-DBUILD_SKEW=unittest".format(**arguments),
                "-DBUILD_VERSION={build_version}".format(**arguments),
                "-DCMAKE_C_COMPILER=/usr/bin/x86_64-linux-gnu-gcc",
                "-DCMAKE_CXX_COMPILER=/usr/bin/x86_64-linux-gnu-g++"
            ],
            "{ComponentRoot}".format(ComponentRoot=component.root)
        )
        compile_CMD = Command(
            "Compile",
            [
                "cmake",
                "--build",
                "build/unittest/unittest".format(**arguments)
            ],
            "{ComponentRoot}".format(ComponentRoot=component.root)
        )
        runUnittests_CMD = Command(
            "Run Unittests",
            [
                "ctest",
                "--output-on-failure",
                "--test-dir",
                "build/unittest/unittest".format(**arguments),
                "--output-junit",
                "{coverage_output_root}/{Component}/unittestUnittestLog.xml".format(Component=component.folder, **arguments)
            ],
            "{ComponentRoot}".format(ComponentRoot=component.root)
        )
        generateCoverage_CMD = Command(
            "Generate Coverage",
            [
                "lcov",
                "--capture",
                "--base-directory",
                "./unittest".format(**arguments),
                "--directory",
                "./unittest".format(**arguments),
                "--output-file",
                "{coverage_output_root}/{Component}/unittest_raw.info".format(Component=component.folder, **arguments)
            ],
            "{ComponentRoot}/build/unittest".format(ComponentRoot=component.root)
        )
        filterCoverageExtract_CMD = Command(
            "Filter Coverage: Extract",
            [
                "lcov",
                "--extract",
                "unittest_raw.info".format(**arguments),
                "--output-file",
                "unittest_temp1.info".format(**arguments),
                "*/{Component}/*".format(Component=component.folder),
            ],
            "{coverage_output_root}/{Component}".format(Component=component.folder, **arguments)
        )
        filterCoverageRemove_CMD = Command(
            "Filter Coverage: Remove",
            [
                "lcov",
                "--remove",
                "unittest_temp1.info".format(**arguments),
                "--output-file",
                "unittest.info".format(**arguments),
                "*/test/*"
            ],
            "{coverage_output_root}/{Component}".format(Component=component.folder, **arguments)
        )
        filterCoverageExportToHTML_CMD = Command(
            "Filter Coverage: Export to HTML",
            [
                "genhtml",
                "--title",
                "{Component}".format(Component=component.folder),
                "--show-details",
                "--legend",
                "--output-directory",
                "unittest".format(**arguments),
                "unittest.info".format(**arguments)
            ],
            "{coverage_output_root}/{Component}".format(Component=component.folder, **arguments)
        )

        PrettyPrint().lowPrint("=== {Component} ({i} of {n}) ===".format(Component=component.folder, i=componentIndex, n=componentCount)).indent()
        componentIndex += 1

        if(component.hasTests):
            if(arguments["generate_build_files"]):
                generateBuildFiles_CMD.execute(arguments["silent"])
            if(arguments["compile"]):
                compile_CMD.checkExecute(generateBuildFiles_CMD, arguments["silent"])
            if(arguments["run_unittests"]):
                runUnittests_CMD.checkExecute(compile_CMD, arguments["silent"])
            if(arguments["generate_coverage"]):
                generateCoverage_CMD.checkExecute(runUnittests_CMD, arguments["silent"])
                filterCoverageExtract_CMD.checkExecute(generateCoverage_CMD, arguments["silent"])
                filterCoverageRemove_CMD.checkExecute(filterCoverageExtract_CMD, arguments["silent"])
                filterCoverageExportToHTML_CMD.checkExecute(filterCoverageRemove_CMD, arguments["silent"])
        PrettyPrint().dedent()
            
    ########################################

    if(arguments["merge_coverage"]):
        filterCoverageMerge_CMD = Command(
            "Filter Coverage: Merge",
            [
                "lcov",
                "--add-tracefile"
            ] + generateTracefileAdd(arguments) + [
                "--output-file",
                "unittest.info".format(**arguments),
            ] ,
            "{coverage_output_root}/merged".format(**arguments)
        )
        filterCoverageExportMergeToHTML_CMD = Command(
            "Filter Coverage: Export Merge To HTML",
            [
                "genhtml",
                "--title",
                "Merged unittest - Unittest Report".format(**arguments),
                "--show-details",
                "--legend",
                "--output-directory",
                "unittest".format(**arguments),
                "unittest.info".format(**arguments)
            ],
            "{coverage_output_root}/merged".format(**arguments)
        )

        filterCoverageMerge_CMD.makeDirectory().execute(arguments["silent"])
        filterCoverageExportMergeToHTML_CMD.makeDirectory().checkExecute(filterCoverageMerge_CMD, arguments["silent"])

    return

################################################################################
# Setup Parser
################################################################################

def setupParser() -> argparse.ArgumentParser:
    parser = argparse.ArgumentParser(description=CONFIG_DICT["FullName"])
    pythonToolsRoot = os.path.abspath(pathlib.Path(__file__).parent.resolve())

    parser.add_argument("--generate-build-files",
                        action="store_true",
                        help="Generate build files from CMake")
    parser.add_argument("--compile",
                        action="store_true",
                        help="Compile from build files")
    parser.add_argument("--run-unittests",
                        action="store_true",
                        help="Run unittests")
    parser.add_argument("--generate-coverage",
                        action="store_true",
                        help="Generate coverage information")
    parser.add_argument("--merge-coverage",
                        action="store_true",
                        help="Merge filtered coverage into single coverage")
    parser.add_argument("--silent",
                        action="store_false",
                        help="Silence command outputs (has no bearing on script messages)")

    parser.add_argument("--build-version",
                        action="store",
                        default="Y--W--B--",
                        help="The build version you want written in")
    parser.add_argument("--subset",
                        action="store",
                        nargs="*",
                        help="Subset list of all components to cover")
    parser.add_argument("--software-root",
                        action="store",
                        default="{PythonToolsRoot}/../../software".format(PythonToolsRoot=pythonToolsRoot),
                        type=Validate.validateDirectoryPath,
                        help="Path to software root directory")
    parser.add_argument("--coverage-output-root",
                        action="store",
                        default="{PythonToolsRoot}/../../documentation/coverageReport".format(PythonToolsRoot=pythonToolsRoot),
                        type=Validate.validateOrCreateDirectoryPath,
                        help="Path to coverage output root directory")
    
    parser.add_argument("--verbosity",
                        action="store",
                        default=0,
                        type=Validate.validateVerbosity,
                        help="Sets the depth of information printed (0=Low, 1=Medium, 2=High)")

    return parser

################################################################################
# Main Call
################################################################################

if __name__ == "__main__":
    PrettyPrint(CONFIG_DICT)
    arguments = setupParser().parse_args()
    PrettyPrint().verbosity = vars(arguments)["verbosity"]
    main(vars(arguments))

################################################################################
