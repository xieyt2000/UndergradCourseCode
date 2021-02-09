import re
import function
import numpy as np
from constants import *


# fit the pre-trained embedding to vocabulary to increase speed
def build_embedding(word2id, ori_emb_path):
    embedding = {}
    with open(ori_emb_path) as file:
        lines = file.readlines()
        embedding['dimension'] = int(lines[0].split(' ')[1])
        emb_list = [[0.0] * embedding['dimension']] * len(word2id)
        for line in lines[1:]:
            line_list = line.strip().split(' ')
            if line_list[0] in word2id:
                emb_list[word2id[line_list[0]]] = list(map(float, line_list[1:]))
    embedding['list'] = emb_list
    function.write_json_file(EMBEDDING_PATH, embedding)
    print(f"Embedding built. Saved at {EMBEDDING_PATH}.")


def build_vocabulary(texts):
    word_count = {}
    for sentence in texts:
        word_list = sentence.split(' ')
        for word in word_list:
            if word in word_count:
                word_count[word] += 1
            else:
                word_count[word] = 1
    function.write_json_file(WORD_COUNT_PATH, word_count)
    vocab_list = list(word_count.items())
    vocab_list.sort(key=lambda x: x[1], reverse=True)
    vocab_list.extend([(UNKNOWN, 0), (PADDING, 0)])
    word2id = {}
    for idx, word in enumerate(vocab_list):
        word2id[word[0]] = idx
    function.write_json_file(WORD2ID_PATH, word2id)
    print(f"{len(word_count)} words in vocabulary. "
          f"Saved at {WORD_COUNT_PATH} and {WORD2ID_PATH}.")
    return word2id


def remove_redundant(text):
    text = re.sub(r"[^\u4e00-\u9fa50-9\s]", '', text)  # keep chinese, numbers and whitespace
    text = re.sub(r"\d{8,}", '', text)  # delete long number (phone, date)
    text = re.sub(r" +", ' ', text)  # multiple spaces
    return text.strip()


def convert(input_path, output_path):
    with open(input_path) as file:
        lines = file.readlines()
    processed_news = []
    for line in lines:
        news_piece = {}
        sina_id, emotions, text = line.split('\t')
        emotions = emotions.split(' ')
        news_piece['total_votes'] = emotions[0].split(':')[1]
        emotion_vec = []
        for e_text in emotions[1:]:
            e_type, e_votes = e_text.split(':')
            emotion_vec.append(int(e_votes))
        max_vote = max(emotion_vec)
        if emotion_vec.count(max_vote) > 1:
            # multiple emotions with highest votes. can't label, skip this entry
            continue
        news_piece['label'] = emotion_vec.index(max_vote)
        news_piece['emotions'] = emotion_vec
        text = remove_redundant(text)
        news_piece['text'] = text
        processed_news.append(news_piece)
    function.write_json_file(output_path, processed_news)
    print(f"Finish preprocesssing {input_path}. {str(len(processed_news))} entries. "
          f"Saved at {output_path}.")
    return processed_news


def preprocess(sina_folder_path, ori_embed_path):
    convert(sina_folder_path + "/sinanews.test", TEST_PATH)
    train_data = convert(sina_folder_path + "/sinanews.train", TRAIN_PATH)
    word2id = build_vocabulary(function.data2vec(train_data)[0])
    build_embedding(word2id, ori_embed_path)
