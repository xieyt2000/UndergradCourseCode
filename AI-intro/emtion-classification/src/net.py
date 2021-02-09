"""
neural networks for deep learning
"""

import torch
import torch.nn as nn
from constants import *
import torch_data


class FastText(nn.Module):
    def __init__(self, config):
        super().__init__()
        self.embedding = nn.Embedding.from_pretrained(torch_data.get_embedding())
        self.fc = nn.Linear(EMBEDDING_DIM, EMOTIONS_NUM)
        self.dropout = nn.Dropout(config['dropout'])

    def forward(self, texts):
        x = self.embedding(texts)
        x = self.dropout(x)
        x = x.mean(1)
        x = self.fc(x)
        return x


class MLP(nn.Module):
    def __init__(self, config):
        super().__init__()
        self.embedding = nn.Embedding.from_pretrained(torch_data.get_embedding())
        self.fc1 = nn.Linear(config['sentence_len'] * EMBEDDING_DIM, config['hidden_size'])
        self.activation = nn.ReLU()
        self.fc2 = nn.Linear(config['hidden_size'], EMOTIONS_NUM)
        self.dropout = nn.Dropout(config['dropout'])

    def forward(self, texts):
        x = self.embedding(texts)
        x = self.fc1(x.view(x.size(0), -1))
        x = self.activation(x)
        x = self.dropout(x)
        x = self.fc2(x)
        return x


class RCNN(nn.Module):
    def __init__(self, config):
        super().__init__()
        self.embedding = nn.Embedding.from_pretrained(torch_data.get_embedding())
        self.lstm = nn.LSTM(EMBEDDING_DIM, config['hidden_size'], config['num_layers'],
                            batch_first=True, bidirectional=True)
        self.fc1 = nn.Linear(config['hidden_size'] * 2 + EMBEDDING_DIM, config['hidden_size'])
        self.pool = nn.MaxPool1d(config['sentence_len'])
        self.fc2 = nn.Linear(config['hidden_size'], EMOTIONS_NUM)
        self.dropout = nn.Dropout(config['dropout'])

    def forward(self, texts):
        embeddings = self.embedding(texts)
        x = self.lstm(embeddings)[0]
        x = torch.cat((embeddings, x), 2)
        x = self.fc1(x).permute(0, 2, 1)
        x = self.dropout(x)
        x = self.pool(x).squeeze()
        x = self.fc2(x)
        return x


class RNN(nn.Module):
    def __init__(self, config):
        super().__init__()
        self.lstm = nn.LSTM(EMBEDDING_DIM, config['hidden_size'], config['num_layers'], batch_first=True)
        self.embedding = nn.Embedding.from_pretrained(torch_data.get_embedding())
        self.fc = nn.Linear(config['hidden_size'], EMOTIONS_NUM)
        self.dropout = nn.Dropout(config['dropout'])

    def forward(self, texts):
        x = self.embedding(texts)
        x = self.dropout(x)
        x = self.lstm(x)[0]
        x = x.mean(1)
        x = self.fc(x)
        return x


class CNN(nn.Module):
    def __init__(self, config):
        super().__init__()
        self.conv = nn.Conv1d(EMBEDDING_DIM, config['out_channels'],
                              config['kernel_size'], padding=config['kernel_size'] // 2)
        self.embedding = nn.Embedding.from_pretrained(torch_data.get_embedding())
        self.fc = nn.Linear(config['out_channels'], EMOTIONS_NUM)
        self.activation = nn.ReLU()
        self.pool = nn.MaxPool1d(config['sentence_len'])
        self.dropout = nn.Dropout(config['dropout'])

    def forward(self, texts):
        x = self.embedding(texts).permute(0, 2, 1)
        x = self.dropout(x)
        x = self.conv(x)
        x = self.activation(x)
        x = self.pool(x).squeeze()
        x = self.fc(x)
        return x
