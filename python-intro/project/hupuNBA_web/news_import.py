import os

os.environ.setdefault('DJANGO_SETTINGS_MODULE', 'hupuNBA_web.settings')
import django

django.setup()
from news.models import NewsPiece
import json


def import_newspiece_from_json(filename):
    with open(filename) as f:
        for line in f:
            data = json.loads(line)
            title = data['title']
            content = data['content']
            hupu_id = int(data['id'])
            source = data['source']
            time = data['time']
            print(title, content, hupu_id, source, time)
            NewsPiece.objects.get_or_create(newspiece_title=title, newspiece_content=content, hupu_id=hupu_id,
                                            newspiece_source=source, newspiece_time=time)


import_newspiece_from_json("news.json")
