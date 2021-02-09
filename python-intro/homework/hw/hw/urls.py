"""hw URL Configuration

The `urlpatterns` list routes URLs to views. For more information please see:
    https://docs.djangoproject.com/en/1.10/topics/http/urls/
Examples:
Function views
    1. Add an import:  from my_app import views
    2. Add a URL to urlpatterns:  url(r'^$', views.home, name='home')
Class-based views
    1. Add an import:  from other_app.views import Home
    2. Add a URL to urlpatterns:  url(r'^$', Home.as_view(), name='home')
Including another URLconf
    1. Import the include() function: from django.conf.urls import url, include
    2. Add a URL to urlpatterns:  url(r'^blog/', include('blog.urls'))
"""
from django.conf.urls import url
from django.contrib import admin
from . import hw, time, add, list, lists, reply, csv
import django
# import setting
from . import settings

urlpatterns = [
    url(r'^admin/', admin.site.urls),
    url(r'^$', hw.index),
    url(r'^hw/$', hw.indexhw),
    url(r'^time/$', time.current_datetime),
    url(r'^time/plus/(\d{1,2})/', time.hours_ahead),
    url(r'^add/$', add.index),
    url(r'^list/$', list.index),
    url(r'^list1/$', list.index),
    url(r'^list2/$', lists.index),
    url(r'^csv/$', csv.output),
    url(r'^hw/formsubmit/$', reply.index),
    url(r'^static/(?P<path>.*)$', django.views.static.serve, {'document_root': settings.STATIC_ROOT})
]
