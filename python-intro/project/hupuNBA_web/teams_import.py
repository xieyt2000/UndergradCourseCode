import os

os.environ.setdefault('DJANGO_SETTINGS_MODULE', 'hupuNBA_web.settings')
import django

django.setup()
from news.models import Team
import json


def import_teams_from_json(filename):
    with open(filename) as f:
        for line in f:
            data = json.loads(line)
            fullname = data['fullname']
            nickname = data['nickname']
            time = data['enter_NBA_time']
            stadium = data['stadium']
            division = data['division']
            home_page = data['home_page']
            coach = data['coach']
            logo_url = data['logo_url']
            intro = data['intro']
            rosters = data['rosters']
            print(fullname, nickname, time, stadium, division, home_page, coach, logo_url, intro, rosters, sep='\n')
            Team.objects.create(fullname=fullname, nickname=nickname, enter_NBA_time=time, stadium=stadium,
                                division=division, home_page=home_page, coach=coach, logo_url=logo_url, intro=intro,
                                rosters=rosters)


import_teams_from_json("teams.json")
