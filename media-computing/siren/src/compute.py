import jittor
from keys import *


def laplace(y, x):
    grad = gradient(y, x)
    return divergence(grad, x)


def divergence(y, x):
    div = 0.
    for i in range(y.shape[-1]):
        div += jittor.grad(y[..., i], x)[..., i:i + 1]
    return div


def gradient(y, x):
    return jittor.grad(y, x)


def laplace_mse(out, gt):
    channels = gt[IMAGE_KEY].shape[-1]

    if channels == 1:
        out_lap = laplace(out[OUT_KEY], out[IN_KEY])
    elif channels == 3:
        out_lap = []
        for i in range(channels):
            out_lap.append(laplace(out[OUT_KEY][..., i], out[IN_KEY]))
        out_lap = jittor.concat(out_lap, dim=-1)
    else:
        raise ValueError()
    return ((out_lap - gt[LAP_KEY]) ** 2).mean()


def two_grad_mse(out, gt):
    channels = gt[IMAGE_KEY].shape[-1]

    if channels == 1:
        grads = jittor.grad(out[OUT_KEY], out[IN_KEY])
    elif channels == 3:
        grads = []
        for i in range(channels):
            grads.append(jittor.grad(out[OUT_KEY][..., i], out[IN_KEY]))
        grads = jittor.concat(grads, dim=-1)
    else:
        raise ValueError()
    return ((grads - gt[GRAD_KEY]) ** 2).sum(-1).mean()


def mse(out, gt):
    return ((out['out'] - gt) ** 2).mean()
