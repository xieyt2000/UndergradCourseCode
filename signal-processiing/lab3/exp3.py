import numpy as np
from scipy import signal
import matplotlib.pyplot as plt

# 时长为1秒
t = 1
# 采样率为60hz
fs = 60
t_split = np.arange(0, t * fs)

# 1hz与25hz叠加的正弦信号
x_1hz = t_split * 1 * np.pi * 2 / fs
x_25hz = t_split * 25 * np.pi * 2 / fs
signal_sin_1hz = np.sin(x_1hz)
signal_sin_25hz = np.sin(x_25hz)

signal_sin = signal_sin_1hz + 0.25 * signal_sin_25hz


# TODO: 补全这部分代码
# 通带边缘频率为10Hz，
# 阻带边缘频率为22Hz，
# 阻带衰减为44dB，窗内项数为13的汉宁窗函数
# 构建低通滤波器
# 函数需要返回滤波后的信号
def filter_fir(input):
    # TODO: 首先正向对信号滤波(此时输出信号有一定相移)
    window_size = 17
    window_n = np.arange(0, window_size) - (window_size - 1) // 2
    w_c = 2 * np.pi * 16 / fs
    h_n = np.sin(window_n * w_c) / (window_n * np.pi)
    h_n[(window_size - 1) // 2] = w_c / np.pi  # handle zero
    window_fn = 0.5 + 0.5 * np.cos(2 * np.pi / (window_size - 1) * window_n)
    window = h_n * window_fn
    print(window_n, w_c, h_n, window, input, sep='\n')
    convolve = np.convolve(window, input)
    return convolve[0:fs]  # 按照课堂slides的说法，应该是圆卷积。但是圆卷积与助教的示例图差异较大，于是直接取线卷积前60位


# 将输出信号反向，再次用该滤波器进行滤波
# 再将输出信号反向
# 函数需要返回零相位滤波后的信号
def filter_zero_phase(input):
    filter = filter_fir(input)
    reverse = np.flip(filter)
    filter_reverse = filter_fir(reverse)
    return np.flip(filter_reverse)


if __name__ == "__main__":
    delay_filtered_signal = filter_fir(signal_sin)
    zerophase_filtered_signal = filter_zero_phase(signal_sin)

    plt.plot(t_split, signal_sin, label='origin')
    plt.plot(t_split, delay_filtered_signal, label='fir')
    plt.plot(t_split, zerophase_filtered_signal, label='zero phase')

    plt.show()
