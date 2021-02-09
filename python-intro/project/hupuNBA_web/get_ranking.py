import os

os.environ.setdefault('DJANGO_SETTINGS_MODULE', 'hupuNBA_web.settings')
import django

django.setup()
from news.models import *
import json
import jieba


def print_ranking():
    all_teams = {}
    team_list = Team.objects.all()
    for i in team_list:
        nickname = i.nickname
        search = nickname
        if nickname == '76人':
            search = '76'
        val_dict = json.loads(InvertedIndex.objects.filter(key_word=search)[0].value_each_article)
        hot = 0
        for j in val_dict.values():
            hot += j
        all_teams[nickname] = hot
    sorted_all_teams = sorted(all_teams.items(), key=lambda d: d[1], reverse=True)
    for i in sorted_all_teams:
        nickname = i[0]
        hot = i[1]/50
        print('<tr>')
        print(f"<td class=\"text-left\"><a href=\"{{% url 'team'%}}?wd={nickname}\">{nickname}</a></td>")
        print(f'<td class="text-left">{hot}</td>')
        print('</tr>')


print_ranking()
