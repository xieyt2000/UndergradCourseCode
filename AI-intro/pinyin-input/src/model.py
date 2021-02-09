from collections import defaultdict
import function
from constants import *
import heapq


class Model:
    """
    sentences fed to model should begin with (n_gram - 1) * 2 'b' as beginning notation
    and every char in sentences should be like "我0" or "bb"
    """

    def __init__(self, n, fre_dic=None, tot_char=0):
        if fre_dic is None:
            fre_dic = defaultdict(int)
        self._frequency_dic = fre_dic
        self._total_chars = tot_char
        self.n = n

    @classmethod  # factory
    def input_dict(cls, model_dict):
        return cls(model_dict['n'], model_dict['frequency dict'], model_dict["total chars"])

    # prefix and char are strings
    def put(self, prefix, char):
        self._frequency_dic[prefix + char] += 1

    # recursively put all possible [prefixes][char] for padding. prefix and char are strings
    def recur_put(self, prefix, char):
        if len(prefix) < 2:
            return
        self.put(prefix, char)
        if len(prefix) > 2:
            self.recur_put(prefix[2:], char)

    def train(self, sentence):
        length = len(sentence)
        self._total_chars += length / 2 - self.n  # ignore bb and ee in total_chars
        char_list = []
        for i in range(0, length, 2):
            char_list.append(sentence[i:(i + 2)])
        for index, char in enumerate(char_list):
            self.put(char, "")
            if index > self.n - 1:
                prefix = ''.join(char_list[index - (self.n - 1):index])  # prefix as a string like 'bb啊0'
            else:
                prefix = ''.join(char_list[0:index])
            self.recur_put(prefix, char)

    def to_dict(self):
        return {'n': self.n, "total chars": self._total_chars, "frequency dict": self._frequency_dic}

    def cal_conditional_prob(self, prefix, char):
        # assert self._frequency_dic[prefix] != 0
        if prefix in self._frequency_dic:
            return self._frequency_dic.get(prefix + char, 0) / self._frequency_dic[prefix]
        return 0  # prefix not in dict, prob = 0

    def cal_prob_with_smooth(self, prefix, char, beta=SMOOTH_PAR):
        lamb_sum, prob = 0, 0
        for prefix_len in range((self.n - 1) * 2, 1, -2):
            cur_prefix = prefix[-prefix_len:]
            cur_prefix_count = self._frequency_dic.get(cur_prefix, 0)
            if cur_prefix_count != 0:
                lamb = (1 - lamb_sum) * cur_prefix_count / (cur_prefix_count + beta)
                lamb_sum += lamb
                prob += lamb * self.cal_conditional_prob(cur_prefix, char)
        prob += (1 - lamb_sum) * self._frequency_dic.get(char, 0) / self._total_chars
        return prob

    def get_top_k_prob(self, prob_list, k):
        return heapq.nlargest(k, prob_list, key=lambda x: x[1])

    def viterbi(self, chars_list, search_width=SEARCH_WIDTH, beta=SMOOTH_PAR):
        former = {'bb' * (self.n - 1): ('bb' * (self.n - 1), 1)}  # {str[-(self.n-1):]:(str, prob)]}
        chars_list.append(['ee'])
        for chars in chars_list:
            current = {}  # store the result of this iteration. format like former
            for char in chars:
                for former_key, (former_str, former_prob) in former.items():
                    prob = self.cal_prob_with_smooth(former_key, char, beta) * former_prob
                    cur_key = former_key[2:] + char
                    if prob > current.get(cur_key, ("", -1))[1]:
                        current[cur_key] = (former_str + char, prob)
            if search_width > 0:
                former = dict(heapq.nlargest(search_width,
                                             list(current.items()), key=lambda x: x[1][1]))
            else:
                former = current
        res_str = max(former.values(), key=lambda x: x[1])[0]
        res_str_len = len(res_str) - 2
        return ''.join([
            res_str[i]
            for i in range(2 * (self.n - 1), res_str_len, 2)
        ])

    def convert(self, pinyin_sentence, pinyin2char, search_width=SEARCH_WIDTH, beta=SMOOTH_PAR):
        pinyin_list = pinyin_sentence.strip().lower().split(' ')
        possible_chars_list = []
        for pinyin in pinyin_list:
            if pinyin == '':
                continue
            pinyin = function.pinyin_fix(pinyin)
            try:
                possible_chars_list.append(pinyin2char[pinyin])
            except KeyError:
                return pinyin + " is illegal."
        return self.viterbi(possible_chars_list, search_width, beta)
