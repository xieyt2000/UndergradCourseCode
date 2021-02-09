"""hupuNBA_web URL Configuration

The `urlpatterns` list routes URLs to views. For more information please see:
    https://docs.djangoproject.com/en/2.2/topics/http/urls/
Examples:
Function views
    1. Add an import:  from my_app import views
    2. Add a URL to urlpatterns:  path('', views.home, name='home')
Class-based views
    1. Add an import:  from other_app.views import Home
    2. Add a URL to urlpatterns:  path('', Home.as_view(), name='home')
Including another URLconf
    1. Import the include() function: from django.urls import include, path
    2. Add a URL to urlpatterns:  path('blog/', include('blog.urls'))
"""
from django.contrib import admin
from django.urls import path
from . import views

urlpatterns = [
    path('', views.index, name='index'),
    path('post', views.post_info, name='post_info'),
    path('s', views.search, name='search'),
    path('t', views.team, name='team'),
    path('ajax_get_names', views.get_names, name="ajax_get_names"),
    path('ajax_search', views.ajax_search, name='ajax_search'),
    path('ajax_post_brief', views.ajax_post_brief, name='ajax_post_brief'),
    path('ajax_team', views.ajax_gen_team, name='ajax_team'),
    path('ranking', views.ranking, name='ranking')
]
