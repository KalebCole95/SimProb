
################################################################################
# File:     command.py
# Created:  8/28/2023
# By:       Kaleb C
################################################################################

# Standard Libraries
import enum
import pathlib
import os
import subprocess

# Common Libraries
from common.prettyPrint import PrettyPrint, COLORS

################################################################################
# CommandState Enum
################################################################################

@enum.unique
class CommandState(enum.Enum):
    UNKOWN=enum.auto()
    PASSED=enum.auto()
    FAILED=enum.auto()
    SKIPPED=enum.auto()

################################################################################
# Command Class
################################################################################

class Command():

    ########################################
    # Initialization
    ########################################

    def __init__(self, commandName: str, command: list, executePath: pathlib.Path) -> None:
        self.commandName = commandName
        self.command = command
        self.executePath = os.path.abspath(executePath)
        self.commandState = CommandState.UNKOWN
        self.output = ""
        return

    ########################################
    # Check Execute
    ########################################

    def checkExecute(self, previousCommand: 'Command', captureOutput: bool=False, silentStart: bool=False) -> CommandState:
        if(previousCommand.commandState == CommandState.SKIPPED):
            PrettyPrint().warning("Skipping '{CommandName}', '{PreviousCommandName}' Skipped.".format(CommandName=self.commandName, PreviousCommandName=previousCommand.commandName, **COLORS))
            self.commandState = CommandState.SKIPPED
        elif(previousCommand.commandState == CommandState.FAILED):
            PrettyPrint().warning("Skipping '{CommandName}', '{PreviousCommandName}' Failed.".format(CommandName=self.commandName, PreviousCommandName=previousCommand.commandName, **COLORS))
            self.commandState = CommandState.SKIPPED
        else:
            return self.execute(captureOutput, silentStart)

        return self.commandState

    ########################################
    # Execute
    ########################################

    def execute(self, captureOutput: bool=False, silenceStart: bool=False) -> CommandState:
        if(not silenceStart):
            PrettyPrint().lowPrint("{SecondaryColor}Running '{CommandName}'...".format(CommandName=self.commandName, **COLORS))

        if(not os.path.isdir(self.executePath)):
            PrettyPrint().error("Path not found: {Path}".format(Path=self.executePath))
            self.commandState = CommandState.FAILED
            return self.commandState
        os.chdir(self.executePath)

        PrettyPrint().mediumPrint("{Tab}{BrightBlack}- CMD: {Command}".format(Command=" ".join(self.command), **COLORS))
        PrettyPrint().highPrint("{Tab}{BrightBlack}- Path: {Path}".format(Path=self.executePath, **COLORS))

        try:
            completedProcess = subprocess.run(self.command, capture_output=captureOutput, encoding="UTF-8")
            completedProcess.check_returncode()
            
        except Exception as exception:
            PrettyPrint().error("{Tab}'{CommandName}' Failed!".format(CommandName=self.commandName, **COLORS))
            #PrettyPrint().error("{Tab}Exception: {Error}".format(Error=exception, **COLORS))
            self.commandState = CommandState.FAILED
        else:
            PrettyPrint().success("{Tab}'{CommandName}' Passed!".format(CommandName=self.commandName, **COLORS))
            self.commandState = CommandState.PASSED
        
        if(captureOutput):
            self.output = completedProcess.stdout
            #Write stderr to build output file to capture the build warnings
            print(completedProcess.stderr)
            with open('build_output.txt', 'w') as f:
                f.write(completedProcess.stderr)
        
        return self.commandState

    ########################################
    # Make Directory
    ########################################

    def makeDirectory(self) -> 'Command':
        if(not os.path.isdir(self.executePath)):
            os.mkdir(self.executePath)
        return self

################################################################################