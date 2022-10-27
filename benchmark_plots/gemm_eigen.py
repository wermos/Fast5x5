#!/usr/bin/env python3

import pandas as pd
import matplotlib
import matplotlib.pyplot as plt
import numpy as np

data = pd.read_csv("processed_data/gemm_data.csv", sep=",", header=0, usecols=["name", "cpu_time"])

labels = ['4×4', '6×6', '8×8']

x = np.arange(len(labels)) # the label locations
width = 0.35  # the width of the bars

gemm_eigen_4x4_float_mean = data.iloc[0, 1]
gemm_eigen_6x6_float_mean = data.iloc[4, 1]
gemm_eigen_8x8_float_mean = data.iloc[8, 1]
gemm_eigen_4x4_double_mean = data.iloc[12, 1]
gemm_eigen_6x6_double_mean = data.iloc[16, 1]
gemm_eigen_8x8_double_mean = data.iloc[19, 1]

font = {'family' : 'Ubuntu',
        'size'   : 22}

matplotlib.rc('font', **font)

fig, ax = plt.subplots(figsize=(16, 9))
plt.grid(visible=True, axis='y')
ax.set_axisbelow(True)

ax.bar(x - width/2, [gemm_eigen_4x4_float_mean, gemm_eigen_6x6_float_mean, gemm_eigen_8x8_float_mean], width, label="float matrix")
ax.bar(x + width/2, [gemm_eigen_4x4_double_mean, gemm_eigen_6x6_double_mean, gemm_eigen_8x8_double_mean], width, label="double matrix")

fig.canvas.manager.set_window_title('Eigen GEMM Benchmark Plot')
ax.set_ylabel('Time (ns)')
ax.set_xticks(x, labels)
ax.set_title('Eigen GEMM')
ax.legend()

plt.show()

#plt.savefig("gemm_plot.png")
