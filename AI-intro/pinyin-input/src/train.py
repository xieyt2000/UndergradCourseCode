import os
import function
from constants import *
from model import Model


def train(folder_path, n, model_name):
    model = Model(n)

    def train_file(file_path):
        data = function.read_json_file(file_path)
        for sentence in list(data):
            # add (n_gram - 1) 'bb' to the beginning of the sentence and 'ee' to the end
            sentence = ('bb' * (n - 1)) + sentence + 'ee'
            model.train(sentence)

    all_files_paths = os.listdir(folder_path)
    for rel_path in all_files_paths:
        path = folder_path + "/" + rel_path
        print(f"Begin training with {path}")
        try:
            train_file(path)
        except UnicodeDecodeError:
            print("Illegal file, continue.")
        print(f"training with {path} finished.")
    save_path = MODEL_PATH + f"/{model_name}.json"
    function.write_json_file(save_path, model.to_dict())
    print(f"Training finished. Model saved as {save_path}")
