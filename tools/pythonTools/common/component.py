
################################################################################
# File:     component.py
# Created:  8/28/2023
# By:       Kaleb C
################################################################################

# Standard Libraries
from collections import OrderedDict
import os
import pathlib

# Common Libraries
from common.prettyPrint import PrettyPrint, COLORS

################################################################################

COMPONENT_NAME_LENGTH = 0

################################################################################
# Component Class
################################################################################

class Component():

    ########################################
    # Initialization
    ########################################

    def __init__(self, root: str, prefix: str) -> None:
        self.root = os.path.abspath(root)
        self.name = os.path.basename(self.root)
        self.folder = self.root.removeprefix(prefix)
        self.testCount = self.calculateTestCount()
    
    ########################################
    # Calculate Test Count
    ########################################

    def calculateTestCount(self) -> int:
        testCount = 0

        testRoot = os.path.abspath(os.path.join(self.root, "test"))
        if (not os.path.exists(testRoot)):
            return 0
        
        for file in os.scandir(testRoot):
            if file.is_file() and pathlib.Path(file).suffix == ".cpp":
                filePath = os.path.join(testRoot, file)
                with open(filePath) as fout:
                    for i, line in enumerate(fout):
                        testCount += line.count("TEST")

        return testCount

    ########################################
    # Has Tests
    ########################################

    def hasTests(self) -> bool:
        return self.testCount > 0


################################################################################
#
# *Recursively* list subfolders in the given folder tree.
#
################################################################################

def scanFolderTree(projectRoot):
    subfolders = [f.path for f in os.scandir(projectRoot) if f.is_dir()]
    for folder in list(subfolders):
            subfolders.extend(scanFolderTree(folder))
    return subfolders


################################################################################
#
# Find components in the given project folder tree, where any folder containing
# a CMakeLists.txt is considered a component folder.
#
# Returns a dictionary of the components, orderd by path.
#
################################################################################

def generateComponentDict(projectRoot: str) -> dict:
    global COMPONENT_NAME_LENGTH
    componentDict = {}

    projectRoot = os.path.abspath(projectRoot)

    if (not os.path.exists(projectRoot)):
            PrettyPrint().fatal("Project Root not found: {ProjectRoot}".format(projectRoot))

    folderList = scanFolderTree(projectRoot)
    for folder in folderList:
        cmakePath = os.path.abspath(os.path.join(folder, "CMakeLists.txt"))
        if (os.path.exists(cmakePath)):
            component = Component(folder, projectRoot + "/")
            componentDict[component.folder] = component
            COMPONENT_NAME_LENGTH = max(COMPONENT_NAME_LENGTH, len(component.name))
    componentDict = OrderedDict(sorted(componentDict.items()))            

    return componentDict

################################################################################
# Get Subset of Components Dict
################################################################################

def getSubsetComponentDict(componentDict: dict, subsetList: list) -> dict:
    filteredComponentDict = {}

    for item in subsetList:
        if item in componentDict.keys():
            filteredComponentDict[item] = componentDict[item]

    return filteredComponentDict

################################################################################
# Filter Components Dict
################################################################################

def filterComponentDict(componentDict: dict, filterList: list) -> dict:
    filteredComponentDict = {}

    for key in componentDict.keys():
        if key not in filterList:
            filteredComponentDict[key] = componentDict[key]

    return filteredComponentDict

################################################################################
