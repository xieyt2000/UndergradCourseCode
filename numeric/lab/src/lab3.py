import numpy as np


def get_input(n):
    hilbert = np.zeros((n, n))
    for i in range(n):
        for j in range(n):
            hilbert[i, j] = 1 / (i + j + 1)
    x = np.ones((n, 1))
    b = hilbert @ x
    return hilbert, x, b


def cholesky(matrix: np.ndarray, n):
    """
    :param matrix: constant
    :param n:
    :return: L
    """
    res = matrix.copy()
    for j in range(n):
        for k in range(j):
            res[j, j] -= res[j, k] ** 2
        res[j, j] = np.sqrt(res[j, j])
        for i in range(j + 1, n):
            for k in range(j):
                res[i, j] -= res[i, k] * res[j, k]
            res[i, j] /= res[j, j]
        res[:j, j] = 0  # clear upper triangle
    return res


def solve_with_cholesky(l: np.ndarray, b: np.ndarray, n):
    # Ly = b
    y = b.copy()
    for i in range(n):
        for j in range(i):
            y[i] -= l[i, j] * y[j]
        y[i] /= l[i, i]
    # print(y)
    # L^T x = y
    lt = l.T
    x = y.copy()
    for i in reversed(range(n)):
        for j in reversed(range(i + 1, n)):
            x[i] -= lt[i, j] * x[j]
        x[i] /= lt[i, i]
    return x


def analyze_one_case(n, error):
    hilbert, x_exact, b = get_input(n)
    if error:
        b += 1e-7
    l = cholesky(hilbert, n)
    # print(l)
    x_approx = solve_with_cholesky(l, b, n)
    # print(x_approx)
    r = b - hilbert @ x_approx
    delta_x = x_approx - x_exact
    r_norm = np.linalg.norm(r, ord=np.inf)
    delta_x_norm = np.linalg.norm(delta_x, ord=np.inf)
    print(f"r norm:{r_norm}, delta_x norm:{delta_x_norm}")


def question6():
    for n in (10, 8, 12):
        for error in (False, True):
            print(f"n:{n}, error:{error}")
            analyze_one_case(n, error)
    get_input(10)


if __name__ == '__main__':
    question6()
