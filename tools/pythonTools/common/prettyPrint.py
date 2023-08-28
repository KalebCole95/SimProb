
################################################################################
# File:     PrettyPrint.py
# Created:  8/28/2023
# By:       Kaleb C
################################################################################

# Standard Libraries
import enum
import time
import sys

################################################################################
# Verbosity
################################################################################

@enum.unique
class Verbosity(enum.IntEnum):
    LOW=0
    MEDIUM=1
    HIGH=2

################################################################################
# Color Codes
################################################################################

COLORS = {
    "Black": "\u001b[0m\u001b[30m",
    "Red": "\u001b[0m\u001b[31m",
    "Green": "\u001b[0m\u001b[32m",
    "Yellow": "\u001b[0m\u001b[33m",
    "Blue": "\u001b[0m\u001b[34m",
    "Magenta": "\u001b[0m\u001b[35m",
    "Cyan": "\u001b[0m\u001b[36m",
    "White": "\u001b[0m\u001b[37m",
    "BrightBlack": "\u001b[0m\u001b[30;1m",
    "BrightRed": "\u001b[0m\u001b[31;1m",
    "BrightGreen": "\u001b[0m\u001b[32;1m",
    "BrightYellow": "\u001b[0m\u001b[33;1m",
    "BrightBlue": "\u001b[0m\u001b[34;1m",
    "BrightMagenta": "\u001b[0m\u001b[35;1m",
    "BrightCyan": "\u001b[0m\u001b[36;1m",
    "BrightWhite": "\u001b[0m\u001b[37;1m",
    "Tab": "   ",
    "Reset": "\u001b[0m"
}

################################################################################
# Singleton Metaclass
################################################################################

class Singleton(type):
    _instances = {}
    def __call__(cls, *args, **kwargs):
        if cls not in cls._instances:
            cls._instances[cls] = super(Singleton, cls).__call__(*args, **kwargs)
        return cls._instances[cls]

################################################################################
# Pretty Print
################################################################################

class PrettyPrint(metaclass=Singleton):

    ########################################
    # Constructor
    ########################################

    def __init__(self, configDict: dict) -> None:
        self.__startTime = time.time()
        self.__header = configDict["Header"]
        self.__spacing = ""
        self.verbosity = Verbosity.LOW

        self.__printLookup = COLORS
        self.__printLookup["PrimaryColor"] = COLORS[configDict["PrimaryColor"]]
        self.__printLookup["SecondaryColor"] = COLORS[configDict["SecondaryColor"]]
        self.__printLookup["Shorthand"] = configDict["Shorthand"]
        self.__printLookup["FullName"] = configDict["FullName"]
        self.__printLookup["Base"] = "{PrimaryColor}[ {Shorthand} ]{Reset} ".format(**self.__printLookup)

        self.__start()
        return
    
    ########################################
    # Destructor
    ########################################

    def __del__(self):
        self.__finish()
        return

    ########################################
    # Private Printouts
    ########################################

    def __print(self, message: str) -> None:
        print("{Base}{Spacing}{PrimaryColor}{Message}{Reset}".format(Spacing=self.__spacing.format(**self.__printLookup), Message=message, **self.__printLookup))
        return

    def __start(self) -> None:
        for line in self.__header:
            self.__print(line)
        print()
        return
    
    def __finish(self) -> None:
        self.resetSpacing()
        endString = " {FullName} [Execution Time: {Time:07.3f}] ".format(Time = time.time() - self.__startTime, **self.__printLookup)
        print()
        self.__print("{EndString:#^{Length}s}".format(Length = len(self.__header[0]), EndString=endString))
        return
    
    ########################################
    # Utilities
    ########################################

    def indent(self, count: int=1) -> 'PrettyPrint':
        for ii in range(count):
            self.__spacing += "{Tab}"
        return self
    
    def dedent(self, count: int=1) -> 'PrettyPrint':
        self.__spacing = self.__spacing.replace("{Tab}", "", count)
        return self
    
    def resetSpacing(self) -> 'PrettyPrint':
        self.__spacing = ""
        return self

    ########################################
    # Standard Printouts
    ########################################
    
    def blank(self, includeBase: bool) -> 'PrettyPrint':
        if(includeBase):
            self.__print("")
        else:
            print()
        return self

    def lowPrint(self, message: str) -> 'PrettyPrint':
        if self.verbosity >= Verbosity.LOW:
            self.__print(message)
        return self
    
    def mediumPrint(self, message: str) -> 'PrettyPrint':
        if self.verbosity >= Verbosity.MEDIUM:
            self.__print(message)
        return self
    
    def highPrint(self, message: str) -> 'PrettyPrint':
        if self.verbosity >= Verbosity.HIGH:
            self.__print(message)
        return self
    
    def success(self, message: str) -> 'PrettyPrint':
        self.__print("{BrightGreen}{Message}".format(Message=message, **self.__printLookup))
        return self
    
    def warning(self, message: str) -> 'PrettyPrint':
        self.__print("{BrightYellow}{Message}".format(Message=message, **self.__printLookup))
        return self
    
    def error(self, message: str) -> 'PrettyPrint':
        self.__print("{Red}{Message}".format(Message=message, **self.__printLookup))
        return self
    
    def fatal(self, message: str) -> None:
        self.__print("{BrightRed}{Message}".format(Message=message, **self.__printLookup))
        sys.exit(1)

    ########################################