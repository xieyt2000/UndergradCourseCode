import function
from constants import *
from converter import Converter
import pypinyin
import random


def gen_test_set(file_path, test_count=500, only_long_sentence=True):
    homo_dic = function.read_json_file(HOMO_DIC_PATH)
    all_sentences = function.read_json_file(file_path)
    all_length = len(all_sentences)
    test_index = random.sample(range(0, all_length), test_count)
    answers = []
    inputs = []
    char_count = 0
    for index in test_index:
        sentence = all_sentences[index]
        length = len(sentence)
        if only_long_sentence and length < 10:
            continue
        chars = [
            sentence[i]
            for i in range(0, length, 2)
        ]
        pinyin_ids = [
            int(sentence[i])
            for i in range(1, length, 2)
        ]
        pinyins = []
        for char, pinyin_id in zip(chars, pinyin_ids):
            for dic_pinyin, dic_id in homo_dic[char].items():
                if dic_id == pinyin_id:
                    pinyins.append(dic_pinyin)
                    continue
        answers.append(''.join(chars) + '\n')
        inputs.append(' '.join(pinyins) + '\n')
        char_count += len(chars)
    new_all_sentences = []
    # delete test from training file
    for index, sentence in enumerate(all_sentences):
        if index not in test_index:
            new_all_sentences.append(sentence)

    function.write_json_file(file_path, new_all_sentences)
    with open(TEST_INPUT, "a") as file:
        file.writelines(inputs)
    with open(TEST_ANSWER, "a", encoding='gbk') as file:
        file.writelines(answers)
    print(f"Generate a test set with {len(inputs)} sentences and {char_count} characters. "
          f"Test input added at {TEST_INPUT}. Answer added at {TEST_ANSWER}")


def cmp_file(file_path1, file_path2, encoding='gbk'):
    with open(file_path1, encoding=encoding) as file1, open(file_path2, encoding=encoding) as file2:
        lines1 = file1.readlines()
        lines2 = file2.readlines()
    lines_total, lines_same = 0, 0
    chars_total, chars_same = 0, 0
    for line1, line2 in zip(lines1, lines2):
        lines_total += 1
        if line1 == line2:
            lines_same += 1
        for char1, char2 in zip(line1, line2):
            chars_total += 1
            if char1 == char2:
                chars_same += 1
    print(f"{chars_total} characters in total. {chars_same} characters match. {100 * chars_same / chars_total} %")
    print(f"{lines_total} lines in total. {lines_same} lines match. {100 * lines_same / lines_total} %")


def test(converter, search_width=SEARCH_WIDTH, beta=SMOOTH_PAR):
    assert isinstance(converter, Converter)
    converter.convert_file(TEST_INPUT, TEST_OUTPUT, search_width, beta)
    cmp_file(TEST_OUTPUT, TEST_ANSWER)


def pypinyin_test():
    with open(TEST_ANSWER, encoding='gbk') as file:
        lines = file.read().splitlines()
    output = []
    for line in lines:
        output.append(' '.join(pypinyin.lazy_pinyin(line)) + '\n')
    with open(TEST_OUTPUT, 'w') as file:
        file.writelines(output)
    cmp_file(TEST_INPUT, TEST_OUTPUT, encoding='utf-8')
