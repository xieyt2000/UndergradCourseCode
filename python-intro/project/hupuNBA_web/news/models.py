from django.db import models


# Create your models here.


class NewsPiece(models.Model):
    newspiece_title = models.CharField(max_length=100)
    newspiece_content = models.TextField()
    hupu_id = models.IntegerField()
    newspiece_source = models.CharField(max_length=20)
    newspiece_time = models.CharField(max_length=50)

    def __str__(self):
        return self.newspiece_title


class InvertedIndex(models.Model):
    key_word = models.CharField(max_length=100)
    value_each_article = models.TextField()

    def __str__(self):
        return self.key_word


class Team(models.Model):
    fullname = models.CharField(max_length=50)
    nickname = models.CharField(max_length=10)
    enter_NBA_time = models.CharField(max_length=10)
    stadium = models.CharField(max_length=10)
    division = models.CharField(max_length=10)
    home_page = models.CharField(max_length=50)
    coach = models.CharField(max_length=10)
    logo_url = models.CharField(max_length=50)
    intro = models.CharField(max_length=100)
    rosters = models.TextField()

    def __str__(self):
        return self.fullname
