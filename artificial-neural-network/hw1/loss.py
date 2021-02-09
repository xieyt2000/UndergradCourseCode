from __future__ import division
import numpy as np


class EuclideanLoss(object):
    def __init__(self, name):
        self.name = name

    def forward(self, input, target):
        # TODO START
        return np.linalg.norm(target - input) / (
            2 * input.shape[0]  # batch size
        )
        # TODO END

    def backward(self, input, target):
        # TODO START
        return (input - target) / input.shape[0]
        # TODO END


class SoftmaxCrossEntropyLoss(object):
    def __init__(self, name):
        self.name = name

    def forward(self, input, target):
        # TODO START
        exp = np.exp(input)
        h = exp / (np.sum(exp, axis=1, keepdims=True) + 1e-50)
        e_n = -np.sum(target * np.log(h + 1e-50), axis=1)
        return np.mean(e_n)
        # TODO END

    def backward(self, input, target):
        # TODO START
        exp = np.exp(input)
        h = exp / (np.sum(exp, axis=1, keepdims=True) + 1e-50)
        return (h - target) / input.shape[0]
        # should add "* np.sum(target, axis=1)"
        # to the expression above,
        # but the sum will always be 1 so omit this operation
        # TODO END


class HingeLoss(object):
    def __init__(self, name, threshold=5):  # adjust hyper-para
        self.name = name
        self.threshold = threshold  # bug fix

    def forward(self, input, target):
        # TODO START
        # invert target (0 <-> 1) and assign to condition
        cond = np.ones(target.shape) - target
        correct_predict = np.sum(target * input, axis=1, keepdims=True)
        h = np.maximum(0, self.threshold - correct_predict + input) * cond
        e_n = np.sum(h, axis=1)
        return np.mean(e_n)
        # TODO END

    def backward(self, input, target):
        # TODO START
        cond = np.ones(target.shape) - target
        correct_predict = np.sum(target * input, axis=1, keepdims=True)
        h = (self.threshold - correct_predict + input) * cond
        h_positive = h > 0  # bool matrix where h >0 is true
        # gradient of y_i where i is the label
        h_positive_sum = np.sum(h_positive, axis=1, keepdims=True)  # numbers of positive elements in one input
        grad_label = -h_positive_sum * target
        # gradient of others
        grad_other = h_positive.astype(np.float64)  # omit (* cond) since h_positive at the label is always false
        return (grad_label + grad_other) / input.shape[0]
        # TODO END
