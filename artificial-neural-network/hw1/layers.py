import numpy as np


class Layer(object):
    def __init__(self, name, trainable=False):
        self.name = name
        self.trainable = trainable
        self._saved_tensor = None

    def forward(self, input):
        pass

    def backward(self, grad_output):
        pass

    def update(self, config):
        pass

    def _saved_for_backward(self, tensor):
        '''The intermediate results computed during forward stage
        can be saved and reused for backward, for saving computation'''

        self._saved_tensor = tensor

class Relu(Layer):
    def __init__(self, name):
        super(Relu, self).__init__(name)

    def forward(self, input):
        # TODO START
        '''Your codes here'''
        cond = input > 0
        self._saved_for_backward(cond)
        return cond * input
        # TODO END

    def backward(self, grad_output):
        # TODO START
        '''Your codes here'''
        return self._saved_tensor * grad_output
        # TODO END

class Sigmoid(Layer):
    def __init__(self, name):
        super(Sigmoid, self).__init__(name)

    def forward(self, input):
        # TODO START
        exp = np.exp(-input)
        result = 1 / (1+exp)
        self._saved_for_backward(np.array([exp, result], dtype=np.float64))
        return result
        # TODO END

    def backward(self, grad_output):
        # TODO START
        return grad_output * self._saved_tensor[0] * np.power(
            self._saved_tensor[1], 2)
        # TODO END

class Gelu(Layer):
    def __init__(self, name):
        super(Gelu, self).__init__(name)

    def forward(self, input):
        # TODO START
        angle = np.sqrt(2 / np.pi) * (
                input + 0.044715 * np.power(input, 3))
        tanh = np.tanh(angle)
        result = 0.5 * input * (1 + tanh)
        self._saved_for_backward(np.array([input, angle, tanh],
                                          dtype=np.float64))
        return result
        # TODO END

    def backward(self, grad_output):
        # TODO START
        # Reference: https://www.wolframalpha.com
        x, angle, tanh = self._saved_tensor
        return grad_output * (0.5 + 0.5 * tanh + (
                (0.0535161 * np.power(x, 3) + 0.398942 * x) / (
                    np.power(np.cosh(angle), 2))
        ))
        # TODO END

class Linear(Layer):
    def __init__(self, name, in_num, out_num, init_std):
        super(Linear, self).__init__(name, trainable=True)
        self.in_num = in_num
        self.out_num = out_num
        self.W = np.random.randn(in_num, out_num) * init_std
        self.b = np.zeros(out_num)

        self.grad_W = np.zeros((in_num, out_num))
        self.grad_b = np.zeros(out_num)

        self.diff_W = np.zeros((in_num, out_num))
        self.diff_b = np.zeros(out_num)

    def forward(self, input):
        # TODO START
        self._saved_for_backward(input)
        return input @ self.W + self.b
        # TODO END

    def backward(self, grad_output):
        # TODO START
        input_tensor = self._saved_tensor
        self.grad_b = np.sum(grad_output, axis=0)  # sum of batch
        self.grad_W = input_tensor.T @ grad_output
        return grad_output @ self.W.T
        # TODO END

    def update(self, config):
        mm = config['momentum']
        lr = config['learning_rate']
        wd = config['weight_decay']

        self.diff_W = mm * self.diff_W + (self.grad_W + wd * self.W)
        self.W = self.W - lr * self.diff_W

        self.diff_b = mm * self.diff_b + (self.grad_b + wd * self.b)
        self.b = self.b - lr * self.diff_b
