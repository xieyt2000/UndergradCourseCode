import preprocess
from constants import *
import function
import train
from converter import Converter
import sys
import test


def main():
    while True:
        input_cmd = input("Enter command. Enter \"help\" to check commands available\n")
        if input_cmd == "help":
            print("exit, init pinyin, init char table, preprocess, train, load model, convert sentence, "
                  "convert file, generate file, test")
        elif input_cmd == "exit":
            break
        elif input_cmd == "init pinyin":
            preprocess.init_pinyin(function.input_with_default(PINYIN_PATH))
        elif input_cmd == "init char table":
            preprocess.init_char(function.input_with_default(CHAR_PATH))
        elif input_cmd == "preprocess":
            preprocess.preprocess(function.input_with_default(SINA_PATH),
                                  function.input_with_default("sina", message="name"))
        elif input_cmd == "train":
            train.train(function.input_with_default(TRAINING_DATA_PATH),
                        int(function.input_with_default('2', message="n for n-gram")),
                        function.input_with_default("model", message="name of the model"))
        elif input_cmd == "load model":
            converter = Converter(MODEL_PATH + '/' +
                                  function.input_with_default("model", message="name") + '.json')
        elif input_cmd == "convert sentence":
            print(converter.convert_sentence
                  (function.input_with_default("ni hao", message="sentence"), search_width=-1))
        elif input_cmd == "convert file":
            converter.convert_file(function.input_with_default(INPUT_PATH, message="input path"),
                                   function.input_with_default(OUTPUT_PATH, message="output path")
                                   )
        elif input_cmd == "generate test":
            test.gen_test_set(function.input_with_default(TRAINING_DATA_PATH + "/sina-1.json"),
                              int(function.input_with_default(500, message="number of sentences")))
        elif input_cmd == "test":
            test.test(converter)
        else:
            print("Wrong command. Try \"help\" to see all commands.")


if __name__ == '__main__':
    if len(sys.argv) == 3:  # for command line input
        converter = Converter(MODEL_PATH + "/model.json")
        converter.convert_file(sys.argv[1], sys.argv[2])
    else:
        main()
