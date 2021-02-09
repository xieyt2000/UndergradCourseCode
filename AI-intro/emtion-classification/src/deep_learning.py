"""
deep learning method with pytorch
"""

import torch
import copy
import torch.nn as nn
import function
from constants import *
from torch.optim import Adam
import torch_data
from sklearn.metrics import classification_report
from scipy.stats import pearsonr
from net import *


def test_stat(data_loader, net):
    net.eval()
    g_emotions, g_outputs, g_labels, g_pred_labels = [], [], [], []
    with torch.no_grad():
        for batch_data in data_loader:
            texts, labels, emotions = batch_data
            outputs = net(texts)
            predicted = torch.max(outputs.data, 1)[1]
            g_emotions.extend(emotions.tolist())
            g_outputs.extend(outputs.tolist())
            g_labels.extend(labels.tolist())
            g_pred_labels.extend(predicted.tolist())
    report = classification_report(g_labels, g_pred_labels, digits=4,
                                   target_names=EMOTIONS_LIST, zero_division=0)
    report_dict = classification_report(g_labels, g_pred_labels, digits=4,
                                        target_names=EMOTIONS_LIST, output_dict=True, zero_division=0)
    accuracy = report_dict['accuracy']
    coefficient = 0
    for output, emotion in zip(g_outputs, g_emotions):
        coefficient += pearsonr(output, emotion)[0]
    coefficient /= len(g_outputs)
    return accuracy, coefficient, report


def train(config, net, train_loader, val_loader):
    print("Begin training")
    criteria = nn.CrossEntropyLoss()
    optimizer = Adam(net.parameters(), config['lr'])

    best_accuracy, best_net = 0, None
    for epoch in range(config['epochs']):
        print(f"Epoch {epoch} begins")
        # train
        training_loss = 0.0
        net.train()
        for batch_data in train_loader:
            texts, labels, emotions = batch_data
            optimizer.zero_grad()
            output = net(texts)
            loss = criteria(output, labels)
            training_loss += loss
            loss.backward()
            optimizer.step()
        print(f"Loss: {training_loss / len(train_loader):.4f}")
        # validate
        accuracy = test_stat(val_loader, net)[0]
        print(f"Validation accuracy: {accuracy:.4f}")
        if accuracy > best_accuracy:
            best_accuracy = accuracy
            best_net = copy.deepcopy(net)
            print("Best net update")
        print(f"Epoch {epoch} finishes")

    return best_net


def test(method, train_data, test_data):
    config = function.read_json_file(NET_CONFIG_FOLDER + "/" + method + ".json")
    device = torch.device("cuda:0" if torch.cuda.is_available() else "cpu")
    train_loader, val_loader, test_loader = torch_data.load_data(
        train_data, test_data, config['sentence_len'], config['batch_size'], device)

    if method == 'RNN':
        net = RNN(config)
    elif method == 'MLP':
        net = MLP(config)
    elif method == 'RCNN':
        net = RCNN(config)
    elif method == 'FastText':
        net = FastText(config)
    else:
        net = CNN(config)
    net.to(device)

    if 'load' in config:
        # read pre-trained net
        net.load_state_dict(torch.load(NET_FOLDER + "/" + method))
    else:
        net = train(config, net, train_loader, val_loader)
        if 'save' in config:
            torch.save(net.state_dict(), NET_FOLDER + "/" + method)
    _, coefficient, report = test_stat(test_loader, net)
    print("Test result:")
    print(report)
    print(f"coefficient = {coefficient:.4f}")
