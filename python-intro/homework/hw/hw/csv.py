from django.http import HttpResponse
from django.shortcuts import render

data = ['1','2','3','4']


def output(request):
    return render('csv.html', data)
