#!/usr/bin/env python3

import argparse
import fileinput

parser = argparse.ArgumentParser()

parser.add_argument("-f", "--file", help="Name of the csv file to process", type=str)

args = parser.parse_args()

if args.file:
	with fileinput.input(args.file, inplace=True) as f:
		for line in f:
			if "name" in line:
				# then this is the line with the column names
				print(line, end='')
			if "mean" in line:
				# then this is the line with the mean amount of time taken
				print(line, end='')
