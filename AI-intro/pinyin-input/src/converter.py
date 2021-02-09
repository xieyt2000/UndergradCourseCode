from model import Model
import function
from constants import *
from time import time


class Converter:
    def __init__(self, model_path):
        model_dic = function.read_json_file(model_path)
        self.model = Model.input_dict(model_dic)
        self.pinyin2char = function.read_json_file(PINYIN2CHAR_PATH)
        print("Model loaded.")

    def convert_sentence(self, sentence, search_width=SEARCH_WIDTH, beta=SMOOTH_PAR):
        return self.model.convert(sentence, self.pinyin2char, search_width, beta)

    def convert_file(self, input_path, output_path, search_width=SEARCH_WIDTH, beta=SMOOTH_PAR):
        converted_sentences = []
        with open(input_path, encoding='gbk') as file:
            sentences = file.read().splitlines()
            start_time = time()
            for sentence in sentences:
                converted_sentences.append(self.convert_sentence(sentence, search_width, beta) + '\n')
            end_time = time()
        with open(output_path, 'w', encoding='gbk') as file:
            file.writelines(converted_sentences)
        print(f"Conversion finished. Result saved at {output_path}. Took {end_time - start_time} seconds")
