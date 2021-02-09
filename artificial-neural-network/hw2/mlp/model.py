# -*- coding: utf-8 -*-

import torch
from torch import nn
from torch.nn import init
from torch.nn.parameter import Parameter
import numpy as np
class BatchNorm1d(nn.Module):
	# TODO START
	# Reference: https://pytorch.org/docs/stable/_modules/torch/nn/modules/batchnorm.html
	# Reference: https://cs231n.github.io/assignments2020/assignment2
	def __init__(self, num_features):
		super(BatchNorm1d, self).__init__()
		self.num_features = num_features

		# Parameters
		self.weight = Parameter(torch.ones(num_features), requires_grad=True)
		self.bias = Parameter(torch.zeros(num_features), requires_grad=True)

		# Store the average mean and variance
		self.register_buffer('running_mean', torch.zeros(num_features))
		self.register_buffer('running_var', torch.ones(num_features))
		
		# Initialize your parameter
		self.__epsilon = 1e-10
		self.__momentum = 0.1  # pytorch feature: x_new = momentum * x_observed + (1 - momentum) * x_old

	def forward(self, input: torch.Tensor):
		# input: [batch_size, num_feature_map * height * width]
		if self.training:
			mean = input.mean(dim=0)
			var = input.var(dim=0)
			self.running_mean = self.__momentum * mean + (1 - self.__momentum) * self.running_mean
			self.running_var = self.__momentum * var + (1 - self.__momentum) * self.running_var
			initial = (input - mean) / torch.sqrt(var + self.__epsilon)
		else:
			initial = (input - self.running_mean) / torch.sqrt(self.running_var + self.__epsilon)
		return self.weight * initial + self.bias
	# TODO END

class Dropout(nn.Module):
	# TODO START
	def __init__(self, p=0.5):
		super(Dropout, self).__init__()
		self.p = p

	def forward(self, input: torch.Tensor):
		# input: [batch_size, num_feature_map * height * width]
		device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
		if self.training:
			dropout_mask = torch.bernoulli(torch.full([input.shape[1]], 1-self.p)).to(device=device)
			# dropout
			dropped = dropout_mask * input
			# scale
			return dropped/(1-self.p)
		return input
	# TODO END

class Model(nn.Module):
	def __init__(self, drop_rate=0.5, batch_norm=True):
		super(Model, self).__init__()
		# TODO START
		self.fc1 = nn.Linear(3 * 32 * 32, 256)
		self.bn = BatchNorm1d(256) if batch_norm else nn.Identity()
		self.relu = nn.ReLU()
		self.dropout = Dropout(drop_rate)
		self.fc2 = nn.Linear(256, 10)
		# TODO END
		self.loss = nn.CrossEntropyLoss()

	def forward(self, x, y=None):
		# TODO START
		# the 10-class prediction output is named as "logits"
		x = self.fc1(x)
		x = self.bn(x)
		x = self.relu(x)
		x = self.dropout(x)
		logits = self.fc2(x)
		# TODO END

		pred = torch.argmax(logits, 1)  # Calculate the prediction result
		if y is None:
			return pred
		loss = self.loss(logits, y)
		correct_pred = (pred.int() == y.int())
		acc = torch.mean(correct_pred.float())  # Calculate the accuracy in this mini-batch

		return loss, acc
