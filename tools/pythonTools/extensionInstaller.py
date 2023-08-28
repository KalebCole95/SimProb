#! /usr/bin/python

################################################################################
# File:     installExtensions.py
# Created:  8/28/2023
# By:       Kaleb C
################################################################################

# Standard Libraries
import os
import argparse
import json
import pathlib

# Common Libraries
from common.prettyPrint import PrettyPrint, COLORS
from common import validateArgparse as Validate
from common.command import Command

################################################################################
# Global Variables
################################################################################

CONFIG_DICT = {
    "PrimaryColor": "BrightBlue",
    "SecondaryColor": "Blue",
    "Shorthand": "ExIn",
    "FullName": "Extension Installer",
    "Header": [ # https://patorjk.com/software/taag/#p=display&c=bash&f=Big&t=%0A%0A
        r"##############################################################################################",
        r"#    ______      _                 _               _____           _        _ _              #",
        r"#   |  ____|    | |               (_)             |_   _|         | |      | | |             #",
        r"#   | |__  __  _| |_ ___ _ __  ___ _  ___  _ __     | |  _ __  ___| |_ __ _| | | ___ _ __    #",
        r"#   |  __| \ \/ | __/ _ | '_ \/ __| |/ _ \| '_ \    | | | '_ \/ __| __/ _` | | |/ _ | '__|   #",
        r"#   | |____ >  <| ||  __| | | \__ | | (_) | | | |  _| |_| | | \__ | || (_| | | |  __| |      #",
        r"#   |______/_/\_\\__\___|_| |_|___|_|\___/|_| |_| |_____|_| |_|___/\__\__,_|_|_|\___|_|      #",
        r"##############################################################################################"
    ]
}

################################################################################
# Main
################################################################################

def main(arguments: dict) -> None:

    # Parse Extension Recommendations
    extensionJSON = json.loads(open(arguments["extensions_file"], "r").read())

    for extension in extensionJSON["recommendations"]:
        
        install_CMD = Command(
            "Install: {Extension}".format(Extension=extension),
            [
                "code",
                "--install-extension",
                "{Extension}".format(Extension=extension),
                "--force"
            ],
            "{CWD}".format(CWD=os.getcwd())
        )
        install_CMD.execute()

    return

################################################################################
# Setup Parser
################################################################################

def setupParser() -> argparse.ArgumentParser:
    parser = argparse.ArgumentParser(description=CONFIG_DICT["FullName"])

    parser.add_argument("--extensions-file",
                        action="store",
                        default="{PythonToolsRoot}/../../.vscode/extensions.json".format(PythonToolsRoot=pathlib.Path(__file__).parent.resolve()),
                        type=Validate.validateFilePath,
                        help="Relative path to the extensions.json")
    
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