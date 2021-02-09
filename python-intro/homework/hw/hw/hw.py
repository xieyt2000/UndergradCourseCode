from django.http import HttpResponse
def index(request):
    return HttpResponse("Hello, Django.")
def indexhw(request):
    return HttpResponse("Hello World Demo!")
