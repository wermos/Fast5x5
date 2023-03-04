#!/usr/bin/env python3

import argparse

import pandas as pd
import matplotlib
import matplotlib.pyplot as plt
import numpy as np

parser = argparse.ArgumentParser()

parser.add_argument("-t", "--task", help="Which benchmark task to plot", choices=["gemm", "inversion", "similarity", "free-to-bound", "bound-to-free"], type=str, required=True)
parser.add_argument("-p", "--precision", help="What precision data type to plot the data for", choices=["float", "double"], type=str, default="float", required=False)
parser.add_argument("-o", "--output-format", help="What format to output, i.e. a PNG of the plot, or a window with the plot.", choices=["png", "window"], type=str, default="window", required=False)

args = parser.parse_args()

def row_name(task:str, backend: str, dims: str) -> str:
	if args.precision == "float":
		return f"{task}_{backend}_{dims}_float/repeats:20/real_time/threads:1_mean"
	elif args.precision == "double":
		return f"{task}_{backend}_{dims}_double/repeats:20/real_time/threads:1_mean"

def coord_transform_row_name(task:str, backend: str) -> str:
	if args.precision == "float":
		return f"{task}_{backend}_float/repeats:20/real_time/threads:1_mean"
	elif args.precision == "double":
		return f"{task}_{backend}_double/repeats:20/real_time/threads:1_mean"

if args.task != "free-to-bound" and args.task != "bound-to-free":
	data = pd.read_csv(f"processed_data/{args.task}_data.csv", sep=",", index_col=0, usecols=["name", "cpu_time"], encoding="ascii")
	#pd.set_option('max_colwidth', 120)

	labels = ["4×4", "6×6", "8×8"]

	x = np.arange(len(labels)) # the label locations
	width = 0.175  # the width of the bars

	# Comment the font stuff if the program doesn't work
	font = {"family" : "Ubuntu",
			"size"   : 22}
	matplotlib.rc("font", **font)

	fig, ax = plt.subplots(figsize=(16, 9))
	plt.grid(visible=True, axis="y")
	ax.set_axisbelow(True)

	benchmark_name = row_name(args.task, "eigen", "4x4")
	point1 = data.at[benchmark_name, "cpu_time"]
	benchmark_name = row_name(args.task, "eigen", "6x6")
	point2 = data.at[benchmark_name, "cpu_time"]
	benchmark_name = row_name(args.task, "eigen", "8x8")
	point3 = data.at[benchmark_name, "cpu_time"]

	ax.bar(x - 1.5 * width, [point1, point2, point3], width, color="#034488", label="Eigen")

	benchmark_name = row_name(args.task, "blaze", "4x4")
	point1 = data.at[benchmark_name, "cpu_time"]
	benchmark_name = row_name(args.task, "blaze", "6x6")
	point2 = data.at[benchmark_name, "cpu_time"]
	benchmark_name = row_name(args.task, "blaze", "8x8")
	point3 = data.at[benchmark_name, "cpu_time"]

	ax.bar(x - width/2, [point1, point2, point3], width, color="#ff420e", label="Blaze")

	benchmark_name = row_name(args.task, "fastor", "4x4")
	point1 = data.at[benchmark_name, "cpu_time"]
	benchmark_name = row_name(args.task, "fastor", "6x6")
	point2 = data.at[benchmark_name, "cpu_time"]
	benchmark_name = row_name(args.task, "fastor", "8x8")
	point3 = data.at[benchmark_name, "cpu_time"]

	ax.bar(x + width/2, [point1, point2, point3], width, color="#ffd320", label="Fastor")

	if args.precision == "float":
		benchmark_name = row_name(args.task, "custom", "4x4")
		point1 = data.at[benchmark_name, "cpu_time"]
		benchmark_name = row_name(args.task, "custom", "6x6")
		point2 = data.at[benchmark_name, "cpu_time"]
		benchmark_name = row_name(args.task, "custom", "8x8")
		point3 = data.at[benchmark_name, "cpu_time"]

		ax.bar(x + 1.5 * width, [point1, point2, point3], width, color="#569d1b", label="Custom")
	else:
		benchmark_name = row_name(args.task, "custom", "4x4")
		point1 = data.at[benchmark_name, "cpu_time"]

		ax.bar(x + 1.5 * width, [point1, 0, 0], width, color="#569d1b", label="Custom")

	if args.task == "inversion":
		from matplotlib.ticker import ScalarFormatter, PercentFormatter
		ax.set_yscale("log")
		ax.yaxis.set_major_formatter(ScalarFormatter())
		plt.minorticks_off()
		ax.set_ylim(1, 1000)

	ax.set_ylabel("Time (ns)")
	ax.set_xticks(x, labels)

	if args.task == "gemm":
		ax.set_title(f"{args.precision} Matrix GEMM Benchmarks")
		fig.canvas.manager.set_window_title(f"{args.precision} Matrix GEMM Benchmarks Plot")
	elif args.task == "inversion":
		ax.set_title(f"{args.precision} Matrix Inversion Benchmarks")
		fig.canvas.manager.set_window_title(f"Inversion Benchmarks Plot")
	elif args.task == "similarity":
		ax.set_title(f"{args.precision} Matrix Similarity Benchmarks")
		fig.canvas.manager.set_window_title(f"Similarity Benchmarks Plot")

	ax.legend()

	if args.output_format == "window":
		plt.show()
	elif args.output_format == "png":
		plt.savefig(f"{args.task}_plot_{args.precision}.png")

if args.task == "free-to-bound":
	data = pd.read_csv("processed_data/coord_transform_data.csv", sep=",", index_col=0, usecols=["name", "cpu_time"], encoding="ascii")

	# Comment the font stuff if the program doesn't work
	font = {"family" : "Ubuntu",
			"size"   : 22}
	matplotlib.rc("font", **font)

	fig, ax = plt.subplots(figsize=(16, 9))
	plt.grid(visible=True, axis="y")
	ax.set_axisbelow(True)

	benchmark_name = coord_transform_row_name("freeToBound", "eigen")
	point1 = data.at[benchmark_name, "cpu_time"]

	ax.bar("Eigen", point1, color="#034488")

	benchmark_name = coord_transform_row_name("freeToBound", "blaze")
	point2 = data.at[benchmark_name, "cpu_time"]

	ax.bar("Blaze", point2, color="#ff420e")

	benchmark_name = coord_transform_row_name("freeToBound", "fastor")
	point3 = data.at[benchmark_name, "cpu_time"]

	ax.bar("Fastor", point3, color="#ffd320")

	if args.precision == "float":
		benchmark_name = coord_transform_row_name("freeToBound", "custom")
		point4 = data.at[benchmark_name, "cpu_time"]

		ax.bar("Custom", point4, color="#569d1b")

	ax.set_ylabel("Time (ns)")

	ax.set_title(f"{args.precision} Matrix Free to Bound Coordinate Transform Benchmarks")
	fig.canvas.manager.set_window_title("Free to Bound Coordinate Transform Benchmarks Plot")

	if args.output_format == "window":
		plt.show()
	elif args.output_format == "png":
		plt.savefig(f"freeToBound_plot_{args.precision}.png")

if args.task == "bound-to-free":
	data = pd.read_csv("processed_data/coord_transform_data.csv", sep=",", index_col=0, usecols=["name", "cpu_time"], encoding="ascii")

	# Comment the font stuff if the program doesn't work
	font = {"family" : "Ubuntu",
			"size"   : 22}
	matplotlib.rc("font", **font)

	fig, ax = plt.subplots(figsize=(16, 9))
	plt.grid(visible=True, axis="y")
	ax.set_axisbelow(True)

	benchmark_name = coord_transform_row_name("boundToFree", "eigen")
	point1 = data.at[benchmark_name, "cpu_time"]

	ax.bar("Eigen", point1, color="#034488")

	benchmark_name = coord_transform_row_name("boundToFree", "blaze")
	point2 = data.at[benchmark_name, "cpu_time"]

	ax.bar("Blaze", point2, color="#ff420e")

	benchmark_name = coord_transform_row_name("boundToFree", "fastor")
	point3 = data.at[benchmark_name, "cpu_time"]

	ax.bar("Fastor", point3, color="#ffd320")

	if args.precision == "float":
		benchmark_name = coord_transform_row_name("boundToFree", "custom")
		point4 = data.at[benchmark_name, "cpu_time"]

		ax.bar("Custom", point4, color="#569d1b")

	ax.set_ylabel("Time (ns)")

	ax.set_title(f"{args.precision} Matrix Bound to Free Coordinate Transform Benchmarks")
	fig.canvas.manager.set_window_title("Bound to Free Coordinate Transform Benchmarks Plot")

	if args.output_format == "window":
		plt.show()
	elif args.output_format == "png":
		plt.savefig(f"boundToFree_plot_{args.precision}.png")
