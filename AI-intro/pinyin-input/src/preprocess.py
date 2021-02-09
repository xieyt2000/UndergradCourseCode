import json
import cn2an
from constants import *
import function
import pypinyin
import os


# read pinyin table as json dict
def init_pinyin(pinyin_path):
    pinyin2char = {}
    char2pinyin = {}
    # read file and generate a pinyin2char dict without homograph
    with open(pinyin_path, encoding="gbk") as file:
        lines = file.readlines()
    for line in lines:
        line_arr = line.strip().split(" ")
        pinyin2char[line_arr[0]] = line_arr[1:]
    # homograph init
    for pinyin, chars in pinyin2char.items():
        piyin_new_chars = []
        for char in chars:
            if char in char2pinyin:
                char2pinyin[char][pinyin] = len(char2pinyin[char])
            else:
                char2pinyin[char] = {pinyin: 0}
            piyin_new_chars.append(char + str(char2pinyin[char][pinyin]))
        pinyin2char[pinyin] = piyin_new_chars
    function.write_json_file(HOMO_DIC_PATH, char2pinyin)
    function.write_json_file(PINYIN2CHAR_PATH, pinyin2char)
    print("init pinyin done.")


#  read all chinese characters as json. for efficiency, char_table is a dict.
def init_char(char_path):
    char_table = {}
    with open(char_path, encoding="gbk") as file:
        line = file.readline()
    for char in line:
        char_table[char] = True
    function.write_json_file(CHAR_TABLE_PATH, char_table)
    print("init char table done.")


def preprocess(folder_path, name):
    char_table = function.read_json_file(CHAR_TABLE_PATH)
    homo_dic = function.read_json_file(HOMO_DIC_PATH)

    # cut a line to chinese sentences. if ignore number, skip all sentences with number.
    def cut_sentences(inp_line, ignore_number=False):
        pro_str = ""
        sentences = []
        valid_str = True
        for char in inp_line:
            if char in char_table:
                pro_str += char
            elif char.encode("utf-8").isdigit():
                if not ignore_number:
                    pro_str += char
                else:
                    valid_str = False
            elif char in SEPARATOR:
                if valid_str:
                    sentences.append(pro_str)
                pro_str = ""
                valid_str = True
            # for english characters and other punctuations like " ", "/"
            else:
                continue
        ret_sentences = []
        for sentence in sentences:
            if len(sentence) < 2:  # sentence too short, ignore
                continue
            try:
                ret_sentences.append(cn2an.transform(sentence, mode="an2cn"))
            except ValueError:  # number too long. ignore the sentence.
                continue
        return ret_sentences

    # label value in homo_dic to each character
    def label_homo(sentence):
        pinyins = pypinyin.lazy_pinyin(sentence)
        ret_sentence = ""
        for char, pinyin in zip(sentence, pinyins):
            ret_sentence += char
            pinyin = function.pinyin_fix(pinyin)
            try:
                ret_sentence += str(homo_dic[char][pinyin])
            except KeyError:  # pinyin not in dict. caused by conflicts of pypinyin and "拼音汉字表"
                print(char, pinyin)
                ret_sentence += "0"
        return ret_sentence

    def process_file(file_path, cnt, batch_name):
        all_sentences = []
        if batch_name == 'sina':
            with open(file_path, encoding="gbk") as file:
                lines = file.readlines()
            for line in lines:
                news_piece = json.loads(line)
                title = news_piece["title"]
                content = news_piece["html"]
                all_sentences += cut_sentences(title)
                all_sentences += cut_sentences(content)
        if batch_name == 'weixin':
            with open(file_path) as file:
                lines = file.readlines()
            length = len(lines)
            for line_index in range(0, length, 3):  # get 1/3 of weixin corpus
                content = json.loads(lines[line_index])['content']
                all_sentences += cut_sentences(content, ignore_number=True)
        sentences_with_pinyin = []
        for sentence in all_sentences:
            sentences_with_pinyin.append(label_homo(sentence))
        save_path = TRAINING_DATA_PATH + f"/{name}-{cnt}.json"
        function.write_json_file(save_path, sentences_with_pinyin)
        print(f"{file_path} processed. Saved as {save_path}")

    function.pypinyin_fix()
    all_files_paths = os.listdir(folder_path)
    for index, rel_path in enumerate(all_files_paths):
        path = folder_path + "/" + rel_path
        try:
            print(f"Begin processing {path}")
            process_file(path, index, name)
        except UnicodeDecodeError:
            print("Illegal file, continue.")
