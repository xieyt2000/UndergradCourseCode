import os

import django

os.environ.setdefault("DJANGO_SETTINGS_MODULE", "hupuNBA_web.settings")
django.setup()

import json
from news.models import InvertedIndex
import jieba
from news.models import NewsPiece

word_to_article_weight_dict = {}


def count_word_in_str_to_id_with_value(str_to_count, this_id, value):
    word_list = jieba.cut_for_search(str_to_count)
    global word_to_article_weight_dict
    for word in word_list:
        if word not in word_to_article_weight_dict:
            word_to_article_weight_dict[word] = {}
        if this_id not in word_to_article_weight_dict[word]:
            word_to_article_weight_dict[word][this_id] = 0
        word_to_article_weight_dict[word][this_id] += value


def main():
    all_news = NewsPiece.objects.all()
    count = 0
    for news_piece in all_news:
        title = news_piece.newspiece_title
        hupu_id = news_piece.hupu_id
        content = news_piece.newspiece_content
        count_word_in_str_to_id_with_value(title, hupu_id, 50)
        count_word_in_str_to_id_with_value(content, hupu_id, 1)
        count += 1
    print(word_to_article_weight_dict)
    print(count)
    for key, val in word_to_article_weight_dict.items():
        InvertedIndex.objects.get_or_create(key_word=key, value_each_article=json.dumps(val))


main()
