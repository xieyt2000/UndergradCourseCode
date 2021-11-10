import numpy as np

EPSILON = 1e-10


def power_iteration(matrix: np.ndarray):
    n = matrix.shape[1]
    u = np.zeros((n, 1))
    u[0, 0] = 1
    lambda_k, lambda_prev = np.inf, -np.inf
    while np.abs(lambda_prev - lambda_k) >= EPSILON:
        v = matrix @ u
        lambda_temp = np.max(np.abs(v))
        u = v / lambda_temp
        lambda_k, lambda_prev = lambda_temp, lambda_k
    print(f"eigenvalue:{lambda_k}\neigenvector:{u}")


def question1():
    a = np.array([
        [5, -4, 1],
        [-4, 6, -4],
        [1, -4, 7]])
    b = np.array([
        [25, -41, 10, -6],
        [-41, 68, -17, 10],
        [10, -17, 5, -3],
        [-6, 10, -3, 2]
    ])
    print("Matrix A")
    power_iteration(a)
    print("Matrix B")
    power_iteration(b)


def sign(x):
    return 1 if x >= 0 else -1


def householder_qr(matrix: np.ndarray):
    """
    :param matrix: square matrix
    :return:
    """
    n = matrix.shape[1]
    r = matrix.copy()
    q = np.eye(n)
    for k in range(n):
        sigma_k = sign(r[k, k]) * np.linalg.norm(r[k:, k])
        if sigma_k == r[k, k]:
            continue
        v = np.concatenate((np.zeros((k, 1)), r[k:, k:k + 1]))
        v[k] += sigma_k
        beta = v.T @ v
        w = v / np.sqrt(beta)
        h = (np.eye(n) - 2 * w @ w.T)
        q = q @ h
        r = h @ r
    return q, r


def question3(matrix: np.ndarray):
    print("Question 3")
    matrix_prev = matrix + 100
    while np.linalg.norm(matrix_prev - matrix) > EPSILON:
        q, r = householder_qr(matrix)
        matrix_prev, matrix = matrix, r @ q
        print(matrix)


def question4(matrix: np.ndarray):
    print("Question 4")
    matrix_prev = matrix + 100
    n = matrix.shape[1]
    while np.linalg.norm(matrix_prev - matrix) > EPSILON:
        sk = matrix[n - 1, n - 1]
        q, r = householder_qr(matrix - sk * np.eye(n))
        matrix_prev, matrix = matrix, r @ q + sk * np.eye(n)
        print(matrix)


def question34():
    a = np.array([
        [0.5] * 4,
        [0.5] * 2 + [-0.5] * 2,
        [0.5, -0.5, 0.5, -0.5],
        [0.5, -0.5, -0.5, 0.5]
    ])
    question3(a)
    question4(a)


if __name__ == '__main__':
    question1()
    question34()
