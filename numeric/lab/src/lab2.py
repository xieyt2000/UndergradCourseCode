from scipy.optimize import root_scalar

EPSILON = 1e-10
LAMBDA0 = 0.9


def newton(f, der, x0):
    x = x0
    k = 0
    while abs(f(x)) > EPSILON:
        s = f(x) / der(x)
        x_next = x - s
        lambda_i = LAMBDA0
        while abs(f(x_next)) >= abs(f(x)):
            x_next = x - lambda_i * s
            lambda_i *= 0.5
        x = x_next
        k += 1
        print(f"step:{k}, x_k:{x}, lambda:{lambda_i}")
    return x


def compare(fun, der, x0):
    print(root_scalar(fun, x0=x0, x1=x0 + 1, method='secant'))
    print(newton(fun, der, x0))


def question2():
    f1 = lambda x: x ** 3 - x - 1
    d1 = lambda x: 3 * x ** 2 - 1
    f2 = lambda x: -x ** 3 + 5 * x
    d2 = lambda x: -3 * x ** 2 + 5
    compare(f1, d1, 0.6)
    compare(f2, d2, 1.35)


if __name__ == '__main__':
    question2()
