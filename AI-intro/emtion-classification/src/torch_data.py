"""
load the data into pytorch format
"""

import torch
from torch.utils.data import Dataset, DataLoader
import function
from constants import *


class MyDataset(Dataset):
    def __init__(self, sentence_len, news_data, device):
        super().__init__()
        self.device = device
        self.sentence_len = sentence_len
        self.texts_id, self.labels, self.emotions = self.data2tensor_vocab(news_data)

    def __getitem__(self, idx):
        return self.texts_id[idx], self.labels[idx], self.emotions[idx]

    def __len__(self):
        return len(self.labels)

    def data2tensor_vocab(self, news_data):
        word2id = function.read_json_file(WORD2ID_PATH)
        sentences, labels, emotions = function.data2vec(news_data)
        texts_id = []
        for sentence in sentences:
            word_list = sentence.split(' ')
            words_id = []
            for word in word_list:
                words_id.append(word2id.get(word, word2id[UNKNOWN]))
            if len(words_id) < self.sentence_len:
                # padding
                words_id.extend([word2id[PADDING]] * (self.sentence_len - len(words_id)))
            texts_id.append(words_id[:self.sentence_len])
        return (torch.tensor(texts_id).to(self.device),
                torch.tensor(labels).to(self.device), torch.tensor(emotions).to(self.device))


def get_data_loader(news_data, sentence_len, batch_size, device):
    dataset = MyDataset(sentence_len, news_data, device)
    data_loader = DataLoader(dataset=dataset, batch_size=batch_size)
    return data_loader


def load_data(train_data, test_data, sentence_len, batch_size, device):
    train_loader = get_data_loader(train_data, sentence_len, batch_size, device)
    # half of test data extracted as val data
    val_loader = get_data_loader(test_data[:len(test_data) // 2],
                                 sentence_len, batch_size, device)
    test_loader = get_data_loader(test_data[len(test_data) // 2:],
                                  sentence_len, batch_size, device)
    return train_loader, val_loader, test_loader


def get_embedding():
    embedding = function.read_json_file(EMBEDDING_PATH)
    return torch.tensor(embedding['list'])
