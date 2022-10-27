#!/usr/bin/env python3

import pandas as pd
import matplotlib
import matplotlib.pyplot as plt
import numpy as np

data = pd.read_csv("processed_data/gemm_data.csv", sep=",", header=0, usecols=["name", "cpu_time"])

labels = ['4×4', '6×6', '8×8']

x = np.arange(len(labels)) # the label locations
width = 0.35  # the width of the bars

gemm_fastor_4x4_float_mean = data.iloc[3, 1]
gemm_fastor_6x6_float_mean = data.iloc[7, 1]
gemm_fastor_8x8_float_mean = data.iloc[11, 1]
gemm_fastor_4x4_double_mean = data.iloc[15, 1]
gemm_fastor_6x6_double_mean = data.iloc[18, 1]
gemm_fastor_8x8_double_mean = data.iloc[21, 1]

font = {'family' : 'Ubuntu',
        'size'   : 22}

matplotlib.rc('font', **font)

fig, ax = plt.subplots(figsize=(16, 9))
plt.grid(visible=True, axis='y')
ax.set_axisbelow(True)

ax.bar(x - width/2, [gemm_fastor_4x4_float_mean, gemm_fastor_6x6_float_mean, gemm_fastor_8x8_float_mean], width, label="float matrix")
ax.bar(x + width/2, [gemm_fastor_4x4_double_mean, gemm_fastor_6x6_double_mean, gemm_fastor_8x8_double_mean], width, label="double matrix")

fig.canvas.manager.set_window_title('Fastor GEMM Benchmark Plot')
ax.set_ylabel('Time (ns)')
ax.set_xticks(x, labels)
ax.set_title('Fastor GEMM')
ax.legend()

plt.show()

#plt.savefig("gemm_plot.png")
