import json
import pypinyin

def read_json_file(path, encoding="gbk"):
    with open(path, encoding=encoding) as file:
        return json.load(file, encoding=encoding)


# match pypinyin-style result to pinyin in pinyin table
def pinyin_fix(pinyin):
    if pinyin == "nve":
        return "nue"
    if pinyin == "lve":
        return "lue"
    return pinyin


def write_json_file(path, obj, encoding="gbk"):
    with open(path, encoding=encoding, mode="w") as file:
        json.dump(obj, file, ensure_ascii=False)


def input_with_default(default_val, message="path"):
    val = input(f"Enter {message}.\n")
    if val == "":
        val = default_val
    return val

# fix some bugs of pypinyin
def pypinyin_fix():
    pypinyin.load_phrases_dict({"哪些": [["na"], ["xie"]]})
    pypinyin.load_phrases_dict({"哪个": [["na"], ["ge"]]})
    pypinyin.load_phrases_dict({"那些": [["na"], ["xie"]]})
    pypinyin.load_phrases_dict({"白干": [["bai"], ["gan"]]})
    pypinyin.load_phrases_dict({"寻思": [["xun"], ["si"]]})
    pypinyin.load_phrases_dict({"清寒": [["qing"], ["han"]]})
    pypinyin.load_phrases_dict({"补齐": [["bu"], ["qi"]]})
    pypinyin.load_phrases_dict({"添砖加瓦": [["tian"], ["zhuan"], ["jia"], ["wa"]]})
    pypinyin.load_phrases_dict({"敬业乐群": [["jing"], ["ye"], ["le"], ["qun"]]})
    pypinyin.load_phrases_dict({"物竞天择": [["wu"], ["jing"], ["tian"], ["ze"]]})
    pypinyin.load_phrases_dict({"心存疑虑": [["xin"], ["cun"], ["yi"], ["lv"]]})
    pypinyin.load_phrases_dict({"避免麻烦": [["bi"], ["mian"], ["ma"], ["fan"]]})
    pypinyin.load_phrases_dict({"叶落归根": [["ye"], ["luo"], ["gui"], ["gen"]]})
    pypinyin.load_phrases_dict({"地动山摇": [["di"], ["dong"], ["shan"], ["yao"]]})
    pypinyin.load_single_dict({ord("帧"): "zhen"})
    pypinyin.load_single_dict({ord("霰"): "xian"})
    pypinyin.load_single_dict({ord("珩"): "heng"})
    pypinyin.load_single_dict({ord("嗯"): "en"})
    pypinyin.load_single_dict({ord("嗲"): "dia"})
    pypinyin.load_single_dict({ord("豉"): "chi"})
    pypinyin.load_single_dict({ord("聒"): "guo"})
