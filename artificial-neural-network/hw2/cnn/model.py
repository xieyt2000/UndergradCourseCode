# -*- coding: utf-8 -*-

import torch
from torch import nn
from torch.nn import init
from torch.nn.parameter import Parameter
class BatchNorm2d(nn.Module):
	# TODO START
	def __init__(self, num_features):
		super(BatchNorm2d, self).__init__()
		self.num_features = num_features
		shape = (1, num_features, 1, 1)
		# Parameters
		self.weight = Parameter(torch.ones(shape, requires_grad=True))
		self.bias = nn.Parameter(torch.zeros(shape, requires_grad=True))

		# Store the average mean and variance
		self.register_buffer('running_mean', torch.zeros(shape))
		self.register_buffer('running_var', torch.ones(shape))

		# Initialize your parameter
		self.__epsilon = 1e-10
		self.__momentum = 0.1  # pytorch feature: x_new = momentum * x_observed + (1 - momentum) * x_old

	def forward(self, input: torch.tensor):
		# input: [batch_size, num_feature_map, height, width]
		if self.training:
			# different units in same feature map with same mean and var
			mean = input.mean(dim=(0, 2, 3), keepdims=True)
			var = input.var(dim=(0, 2, 3), keepdims=True)
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

	def forward(self, input: torch.tensor):
		# input: [batch_size, num_feature_map, height, width]
		device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
		if self.training:
			dropout_mask = torch.bernoulli(torch.full(tuple(input.shape[1:4]), 1 - self.p)).to(device=device)
			# dropout
			dropped = dropout_mask * input
			# scale
			return dropped / (1 - self.p)
		return input
	# TODO END

class Model(nn.Module):
	def __init__(self, drop_rate=0.5, batch_norm=True):
		super(Model, self).__init__()
		# TODO START
		# Define your layers here
		self.pool = nn.MaxPool2d(2, 2)
		self.relu = nn.ReLU()
		self.dropout = Dropout(drop_rate)
		self.conv1 = nn.Conv2d(3, 64, 5)
		self.bn1 = BatchNorm2d(64) if batch_norm else nn.Identity()
		self.conv2 = nn.Conv2d(64, 256, 5)
		self.bn2 = BatchNorm2d(256) if batch_norm else nn.Identity()
		self.fc = nn.Linear(256 * 5 * 5, 10)
		# TODO END
		self.loss = nn.CrossEntropyLoss()

	def forward(self, x, y=None):	
		# TODO START
		# the 10-class prediction output is named as "logits"
		x = self.conv1(x)
		x = self.bn1(x)
		x = self.relu(x)
		x = self.dropout(x)
		x = self.pool(x)

		x = self.conv2(x)
		x = self.bn2(x)
		x = self.relu(x)
		x = self.dropout(x)
		x = self.pool(x)

		x = x.view(-1, 256 * 5 * 5)
		logits = self.fc(x)
		# TODO END

		pred = torch.argmax(logits, 1)  # Calculate the prediction result
		if y is None:
			return pred
		loss = self.loss(logits, y)
		correct_pred = (pred.int() == y.int())
		acc = torch.mean(correct_pred.float())  # Calculate the accuracy in this mini-batch

		return loss, acc