import csv
from csv import reader, DictReader
import sys
import random
from pandas import DataFrame
from sys import argv, exit

name = ""

def main():
    if len(argv) != 3:
        sys.exit("Usage: python dna.py data.csv sequence.txt")

    with open(argv[1], "r") as csvfile:
        reader = DictReader(csvfile)
        dicthold = list(reader)

    with open(argv[2], "r") as file:
        seqhold = file.read()

    longestrun = []

    for a in range(1, len(reader.fieldnames)):
        dnaS = reader.fieldnames[a]
        longestrun.append(0)
        for b in range(len(seqhold)):
            count = 0
            if seqhold[b:(b + len(dnaS))] == dnaS:
                c = 0
                while seqhold[(b + c):(b + c + len(dnaS))] == dnaS:
                    count = count + 1
                    c = c + len(dnaS)
                if count > longestrun[a - 1]:
                    longestrun[a - 1] = count

    for a in range(len(dicthold)):
        check = 0
        for b in range(1, len(reader.fieldnames)):
            if int(longestrun[b - 1]) == int(dicthold[a][reader.fieldnames[b]]):
                check = check + 1
            if check == (len(reader.fieldnames) - 1):
                name = dicthold[a]['name']
                print(dicthold[a]['name'])
                exit(0)
#print(name)
main()
