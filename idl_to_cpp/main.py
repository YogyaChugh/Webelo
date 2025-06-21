import json
from enum import Enum

typesforcpp = {}

class idl_phrase:
    readonly = False
    const = False
    type = typesforcpp
    

started = []

def main(file_path):
    line = 0
    boilerplate = ""
    with open(file_path) as file:
        for i in file:
            keyword = 0
            temp = i.split()
            for j in temp:
                if "[Exposed=" in j:
                    boilerplate += "//Exposed:- " + j[9:-1]
                if j in predefined:
                    boilerplate += "\n" + predefined[j]
            line += 1