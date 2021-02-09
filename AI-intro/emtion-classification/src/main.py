"""
entrance to the program
"""

import argparse
import sys
import baseline_ml
import preprocess
import torch
from constants import *
import function
import deep_learning
import numpy as np


def parse(argv):
    parser = argparse.ArgumentParser()
    parser.add_argument("--command", required=True, choices=['preprocess', 'test'])
    parser.add_argument("--method", choices=['naive_bayes', 'SVM', 'CNN', 'RNN', 'MLP', 'RCNN', 'FastText'], default='naive_bayes')
    parser.add_argument("--preprocess_folder", default=SINA_FOLDER)
    parser.add_argument("--train_path", default=TRAIN_PATH)
    parser.add_argument("--test_path", default=TEST_PATH)
    parser.add_argument("--ori_embedding_path", default=ORI_EMB_PATH)
    parser.add_argument("--embedding_path", default=EMBEDDING_PATH)
    return parser.parse_args(argv)


if __name__ == '__main__':
    args = parse(sys.argv[1:])
    if args.command == 'test':
        test_data = function.read_json_file(args.test_path)
        train_data = function.read_json_file(args.train_path)
        if args.method == 'naive_bayes' or args.method == 'SVM':
            baseline_ml.test(args.method, train_data, test_data)
        else:
            deep_learning.test(args.method, train_data, test_data)
    if args.command == 'preprocess':
        preprocess.preprocess(args.preprocess_folder, args.ori_embedding_path)
