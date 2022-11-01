#!/usr/bin/env python3

import argparse

import pandas as pd
import matplotlib
import matplotlib.pyplot as plt
import numpy as np

parser = argparse.ArgumentParser()

parser.add_argument("-t", "--task", help="Which benchmark task to plot", choices=["gemm", "inversion", "similarity"], type=str, required=True)
parser.add_argument("-b", "--backend", help="What backend's data to plot", choices=["eigen", "custom", "fastor", "blaze"], type=str, required=True)
parser.add_argument("-o", "--output-format", help="What format to output, i.e. a PNG of the plot, or a window with the plot.", choices=["png", "window"], type=str, default="window", required=False)

args = parser.parse_args()

def row_name(task:str, backend: str, dims: str, use_float=True) -> str:
	if use_float:
		return f"{task}_{backend}_{dims}_float/repeats:20/real_time/threads:1_mean"
	else:
		return f"{task}_{backend}_{dims}_double/repeats:20/real_time/threads:1_mean"

data = pd.read_csv(f"processed_data/{args.task}_data.csv", sep=",", index_col=0, usecols=["name", "cpu_time"], encoding="ascii")
#pd.set_option('max_colwidth', 120)

labels = ['4×4', '6×6', '8×8']

x = np.arange(len(labels)) # the label locations
width = 0.35  # the width of the bars

# Comment the font stuff if the program doesn't work
font = {"family" : "Ubuntu",
		"size"   : 22}
matplotlib.rc("font", **font)

fig, ax = plt.subplots(figsize=(16, 9))
plt.grid(visible=True, axis="y")
ax.set_axisbelow(True)

if args.backend == "custom":
	benchmark_name = row_name(args.task, args.backend, "4x4")
	point1 = data.at[benchmark_name, "cpu_time"]
	benchmark_name = row_name(args.task, args.backend, "6x6")
	point2 = data.at[benchmark_name, "cpu_time"]
	benchmark_name = row_name(args.task, args.backend, "8x8")
	point3 = data.at[benchmark_name, "cpu_time"]

	ax.bar(x - width/2, [point1, point2, point3], width, label="float matrix")

	benchmark_name = row_name(args.task, args.backend, "4x4", use_float=False)
	point1 = data.at[benchmark_name, "cpu_time"]

	ax.bar(x + width/2, [point1, 0, 0], width, label="double matrix")
else:
	benchmark_name = row_name(args.task, args.backend, "4x4")
	point1 = data.at[benchmark_name, "cpu_time"]
	benchmark_name = row_name(args.task, args.backend, "6x6")
	point2 = data.at[benchmark_name, "cpu_time"]
	benchmark_name = row_name(args.task, args.backend, "8x8")
	point3 = data.at[benchmark_name, "cpu_time"]

	ax.bar(x - width/2, [point1, point2, point3], width, label="float matrix")

	benchmark_name = row_name(args.task, args.backend, "4x4", use_float=False)
	point1 = data.at[benchmark_name, "cpu_time"]
	benchmark_name = row_name(args.task, args.backend, "6x6", use_float=False)
	point2 = data.at[benchmark_name, "cpu_time"]
	benchmark_name = row_name(args.task, args.backend, "8x8", use_float=False)
	point3 = data.at[benchmark_name, "cpu_time"]

	ax.bar(x + width/2, [point1, point2, point3], width, label="double matrix")

if args.task == "inversion":
	from matplotlib.ticker import ScalarFormatter, PercentFormatter
	ax.set_yscale("log")
	ax.yaxis.set_major_formatter(ScalarFormatter())
	plt.minorticks_off()
	if args.backend == "fastor":
		ax.set_ylim(1, 100)
		ax.yaxis.set_major_formatter(PercentFormatter(xmax=100, decimals=None, symbol=""))
	if args.backend == "eigen" or args.backend == "blaze":
		ax.set_ylim(1, 1000)
	if args.backend == "custom":
		ax.set_ylim(1, 1000)

if args.task == "similarity":
	if args.backend == "eigen":
		from matplotlib.ticker import AutoMinorLocator
		plt.yticks(np.arange(0, 140, step=10))
		ax.yaxis.set_minor_locator(AutoMinorLocator())
	if args.backend == "custom":
		from matplotlib.ticker import AutoMinorLocator
		plt.yticks(np.arange(0, 875, step=50))
		ax.yaxis.set_minor_locator(AutoMinorLocator())

ax.set_ylabel("Time (ns)")
ax.set_xticks(x, labels)

if args.task == "gemm":
	ax.set_title(f"{args.backend.capitalize()} GEMM")
	fig.canvas.manager.set_window_title(f"{args.backend.capitalize()} GEMM Benchmark Plot")
elif args.task == "inversion":
	ax.set_title(f"{args.backend.capitalize()} Inversion")
	fig.canvas.manager.set_window_title(f"{args.backend.capitalize()} Inversion Benchmark Plot")
elif args.task == "similarity":
	ax.set_title(f"{args.backend.capitalize()} Similarity")
	fig.canvas.manager.set_window_title(f"{args.backend.capitalize()} Similarity Benchmark Plot")

ax.legend()

if args.output_format == "window":
	plt.show()
elif args.output_format == "png":
	plt.savefig(f"{args.backend}_plot.png")

