from django.shortcuts import render
from django.views.generic.edit import CreateView
from django.views.generic import ListView

from main.models import Message


class MessageCreate(CreateView):
    model = Message
    fields = ["name", "email", "text"]
    template_name = "create.html"


class MessageList(ListView):
    model = Message
    template_name = "list.html"
