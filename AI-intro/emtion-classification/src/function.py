"""
some basic functions
"""

import json


def read_json_file(path):
    with open(path, mode='r', encoding='utf-8') as file:
        return json.load(file)


def write_json_file(path, obj):
    with open(path, mode='w', encoding='utf-8') as file:
        json.dump(obj, file, ensure_ascii=False)


def data2vec(news_data):
    texts, labels, emotions = [], [], []
    for piece in news_data:
        texts.append(piece['text'])
        labels.append(piece['label'])
        emotions.append(piece['emotions'])
    return texts, labels, emotions
