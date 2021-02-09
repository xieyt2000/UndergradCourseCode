import os

os.environ.setdefault('DJANGO_SETTINGS_MODULE', 'hupuNBA_web.settings')
import django

django.setup()

import json
from news.models import InvertedIndex
import jieba
from news.models import NewsPiece


