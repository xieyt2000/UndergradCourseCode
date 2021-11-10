import numpy as np
import matplotlib.pyplot as plt
import time


def question1():
    M = 1
    epsilon = 1e-16
    h = np.logspace(-16, 0, base=10)
    truncate_err = M * h / 2
    rounding_err = 2 * epsilon / h
    total_err_bound = truncate_err + rounding_err
    true_val = np.cos(1)
    # np default float type is float 64
    approx_val = (np.sin(1 + h) - np.sin(1)) / h
    absolute_error = np.abs(true_val - approx_val)
    plt.plot(h, truncate_err, label='truncation error')
    plt.plot(h, rounding_err, label='rounding error')
    plt.plot(h, total_err_bound, label='total error bound')
    plt.plot(h, absolute_error, label='total error')
    plt.xscale('log', base=10)
    plt.yscale('log', base=10)
    plt.xlabel('step h')
    plt.ylabel('error')
    plt.legend()
    plt.show()


def question3():
    single_sum = np.float32(0)
    n = 1
    while True:
        prev_sum = single_sum
        single_sum += np.float32(1 / n)
        if prev_sum == single_sum:
            break
        n += 1
    print("(1)", n)
    double_sum = np.float64(0)
    for i in range(1, n + 1):
        double_sum += 1 / i
    print("(2)", np.abs(double_sum - single_sum))
    start_time = time.process_time()
    double_sum = np.float64(0)
    measure_n = int(1e8)
    for n in range(1, measure_n + 1):
        double_sum += 1 / n
    elapsed_time = time.process_time() - start_time
    print("(3)", elapsed_time * 5.9 * 1e14 / measure_n)


if __name__ == '__main__':
    question1()
    question3()
