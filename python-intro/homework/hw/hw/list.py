from django.shortcuts import render_to_response

address = [
    {'name': 'San Zhang', 'email': 'zhangsan@gmail.com'},
    {'name': 'Si Li', 'email': 'lisi@thu.edu.cn'},
    {'name': 'Wu Wang', 'email': 'wangwu@sina.cn'}
]


def index(request):
    return render_to_response('list1.html', {'address': address})
