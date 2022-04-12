import jittor
from jittor import nn
import numpy as np
from keys import *

HIDDEN_LAYERS = 3
HIDDEN_FEATURES = 256
IN_FEATURES = 2


def linear_init(first_layer, in_features, out_features):
    linear = nn.Linear(in_features, out_features)
    if first_layer:
        jittor.init.uniform_(linear.weight, (-1 / in_features), (1 / in_features))
    else:
        jittor.init.uniform_(linear.weight, -np.sqrt(6 / in_features) / 30, np.sqrt(6 / in_features) / 30)
    return linear


class Sine(nn.Module):

    def __init__(self):
        super().__init__()

    def execute(self, input_var):
        return jittor.sin(30 * input_var)


class Siren(nn.Module):

    def __init__(self, out_features):
        super().__init__()
        self.net = nn.Sequential(
            linear_init(True, IN_FEATURES, HIDDEN_FEATURES),
            Sine(),
            *[nn.Sequential(linear_init(False, HIDDEN_FEATURES, HIDDEN_FEATURES), Sine()) for _ in
              range(HIDDEN_LAYERS)],
            linear_init(False, HIDDEN_FEATURES, out_features)
        )

    def execute(self, input_var: jittor.Var):
        input_var = input_var.clone().detach()
        out = self.net(input_var)
        return {
            OUT_KEY: out,
            IN_KEY: input_var
        }
