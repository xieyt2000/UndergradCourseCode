import torch
from torch import nn
import torch.nn.functional as F

class RNNCell(nn.Module):
    def __init__(self, input_size, hidden_size):
        super().__init__()
        self.input_size = input_size
        self.hidden_size = hidden_size

        self.input_layer = nn.Linear(input_size, hidden_size)
        self.hidden_layer = nn.Linear(hidden_size, hidden_size, bias=False)

    def init(self, batch_size, device):
        #return the initial state
        return torch.zeros(batch_size, self.hidden_size, device=device)

    def forward(self, incoming, state):
        # flag indicates whether the position is valid. 1 for valid, 0 for invalid.
        output = (self.input_layer(incoming) + self.hidden_layer(state)).tanh()
        new_state = output # stored for next step
        return output, new_state

class GRUCell(nn.Module):
    def __init__(self, input_size, hidden_size):
        super().__init__()
        self.input_size = input_size
        self.hidden_size = hidden_size

        # TODO START
        # intialize weights and layers
        self.update_gate_w = nn.Linear(input_size, hidden_size, bias=False)
        self.update_gate_u = nn.Linear(hidden_size, hidden_size, bias=False)
        self.reset_gate_w = nn.Linear(input_size, hidden_size, bias=False)
        self.reset_gate_u = nn.Linear(hidden_size, hidden_size, bias=False)
        self.act_w = nn.Linear(input_size, hidden_size, bias=False)
        self.act_u = nn.Linear(hidden_size, hidden_size, bias=False)
        # TODO END

    def init(self, batch_size, device):
        # TODO START
        # return the initial state
        return torch.zeros(batch_size, self.hidden_size, device=device)
        # TODO END

    def forward(self, incoming, state):
        # TODO START
        # calculate output and new_state
        z = (self.update_gate_w(incoming) + self.update_gate_u(state)).sigmoid()
        r = (self.update_gate_w(incoming) + self.update_gate_u(state)).sigmoid()
        h_tilde = (self.act_w(incoming) + self.act_u(r * state)).tanh()
        new_state = (1 - z) * state + z * h_tilde
        output = new_state
        return output, new_state
        # TODO END

class LSTMCell(nn.Module):
    def __init__(self, input_size, hidden_size):
        super().__init__()
        self.input_size = input_size
        self.hidden_size = hidden_size

        # TODO START
        # intialize weights and layers
        self.input_gate_w = nn.Linear(input_size, hidden_size)
        self.input_gate_u = nn.Linear(hidden_size, hidden_size, bias=False)
        self.output_gate_w = nn.Linear(input_size, hidden_size)
        self.output_gate_u = nn.Linear(hidden_size, hidden_size, bias=False)
        self.forget_gate_w = nn.Linear(input_size, hidden_size)
        self.forget_gate_u = nn.Linear(hidden_size, hidden_size, bias=False)
        self.act_w = nn.Linear(input_size, hidden_size)
        self.act_u = nn.Linear(hidden_size, hidden_size, bias=False)
        # TODO END

    def init(self, batch_size, device):
        # TODO START
        # return the initial state (which can be a tuple)
        return (torch.zeros(batch_size, self.hidden_size, device=device),  # h
                torch.zeros(batch_size, self.hidden_size, device=device))  # c
        # TODO END

    def forward(self, incoming, state):
        # TODO START
        # calculate output and new_state
        old_h, old_c = state
        i = (self.input_gate_w(incoming) + self.input_gate_u(old_h)).sigmoid()
        o = (self.output_gate_w(incoming) + self.output_gate_u(old_h)).sigmoid()
        f = (self.forget_gate_w(incoming) + self.forget_gate_u(old_h)).sigmoid()
        c_tilde = (self.act_w(incoming) + self.act_u(old_h)).tanh()
        new_c = f * old_c + i * c_tilde
        new_h = o * new_c.tanh()
        output = new_h
        return output, (new_h, new_c)
        # TODO END
