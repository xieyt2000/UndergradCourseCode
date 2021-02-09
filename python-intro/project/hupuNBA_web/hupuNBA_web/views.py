import json
import jieba
from news.models import *
from django.shortcuts import render
from django.http import JsonResponse
import time
import jieba.analyse


def index(request):
    return render(request, "index.html")


def ranking(request):
    return render(request, 'ranking.html')


def search(request):
    s = request.GET.get('wd', '')
    if not s:
        return render(request, "index.html")
    return render(request, "search.html", {'wd': s})


def team(request):
    s = request.GET.get('wd', '')
    if not s:
        return render(request, "index.html")
    return render(request, "team.html", {'wd': s})


def ajax_gen_team(request):
    s = request.GET.get('wd', '')
    if not s:
        return JsonResponse({})
    this_team = Team.objects.filter(nickname=s)
    if len(this_team) < 1:
        return JsonResponse({})
    this_team = this_team[0]
    full_name = this_team.fullname
    logo = this_team.logo_url
    enter_nba_time = this_team.enter_NBA_time
    stadium = this_team.stadium
    home_page_url = this_team.home_page
    coach = this_team.coach
    intro = this_team.intro
    rosters = json.loads(this_team.rosters.replace("'", "\""))
    start_time = time.time()
    query_list = jieba.analyse.extract_tags(''.join(s.split()), withWeight=True)
    result_words = []
    word_list = jieba.cut_for_search(''.join(s.split()))
    for word in word_list:
        result_words.append(word)
    total_result_dic = {}
    for query_word_weight_pair in query_list:
        query_word = query_word_weight_pair[0]
        query_weight = query_word_weight_pair[1]
        tmp_list = InvertedIndex.objects.filter(key_word=query_word)
        dic_str = tmp_list[0].value_each_article
        print(dic_str)
        try:
            this_word_result_dic = json.loads(dic_str)
        except:
            print("no query")
            continue
        for news_id, val in this_word_result_dic.items():
            if news_id in total_result_dic:
                total_result_dic[news_id] += val * query_weight
            else:
                total_result_dic[news_id] = val * query_weight
    total_result_dic = sorted(total_result_dic.items(), key=lambda x: x[1], reverse=True)
    print(total_result_dic)
    res = []
    for pair in total_result_dic:
        res.append(pair[0])
    for name in rosters.values():
        result_words += name.split('-')
    return JsonResponse(
        {'len': len(res), 'cost': '{:.5f}'.format(time.time() - start_time), 'ci': result_words, 'data': res,
         'full_name': full_name, 'logo': logo, 'time': enter_nba_time, 'stadium': stadium, 'home_page': home_page_url,
         'coach': coach, 'intro': intro, 'roster': rosters})


def ajax_search(request):
    s = request.GET.get('wd', '')
    if not s:
        return JsonResponse({})
    start_time = time.time()
    query_list = jieba.analyse.extract_tags(''.join(s.split()), withWeight=True)
    result_words = []
    word_list = jieba.cut(''.join(s.split()))
    for word in word_list:
        result_words.append(word)
    total_result_dic = {}
    for query_word_weight_pair in query_list:
        query_word = query_word_weight_pair[0]
        query_weight = query_word_weight_pair[1]
        tmp_list = InvertedIndex.objects.filter(key_word=query_word)
        try:
            dic_str = tmp_list[0].value_each_article
            print(dic_str)
            this_word_result_dic = json.loads(dic_str)
        except:
            print("no query")
            continue
        for news_id, val in this_word_result_dic.items():
            if news_id in total_result_dic:
                total_result_dic[news_id] += val * query_weight
            else:
                total_result_dic[news_id] = val * query_weight
    total_result_dic = sorted(total_result_dic.items(), key=lambda x: x[1], reverse=True)
    print(total_result_dic)
    res = []
    for pair in total_result_dic:
        res.append(pair[0])
    return JsonResponse(
        {'len': len(res), 'cost': '{:.5f}'.format(time.time() - start_time), 'ci': result_words, 'data': res})


def ajax_post_brief(request):
    l = len(request.GET)
    if not l:
        return JsonResponse({})
    data = dict()
    try:
        for i in range(l):
            x = request.GET.get(str(i))
            tmp = NewsPiece.objects.get(hupu_id=x)
            data[i] = {
                'TID': tmp.hupu_id,
                'title': tmp.newspiece_title,
                'brief': str(tmp.newspiece_content)[:100],
                'time': tmp.newspiece_time,
                'source': tmp.newspiece_source
            }
    except Exception as e:
        return JsonResponse({})
    return JsonResponse(data)


def post_info(request):
    request_id = request.GET.get('id', '')
    if not request_id:
        return render(request, 'error.html')
    data = None
    try:
        data = NewsPiece.objects.get(hupu_id=request_id)
    except Exception as e:
        return render(request, 'error.html')
    return render(request, 'post.html', {
        'NID': data.hupu_id,
        'title': data.newspiece_title,
        'content': data.newspiece_content,
        'time': data.newspiece_time,
        # 'source_link': data.sourceLink,
        'source_text': data.newspiece_source
    })


def get_names(request):
    team_list = Team.objects.all()
    words_to_nickname = {}
    for team in team_list:
        nickname = team.nickname
        player_dict = json.loads(team.rosters.replace("'", "\""))
        words_to_nickname[nickname] = nickname
        for player in player_dict.values():
            words_to_nickname[player] = nickname
    return JsonResponse(words_to_nickname)
