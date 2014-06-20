from django.core.urlresolvers import reverse_lazy
from django.views.generic.edit import CreateView
from django.views.generic import ListView
from django.shortcuts import render_to_response

from main.models import Message
# from main.baulicht_dbus import BaulichtDbus
#
# baulicht = BaulichtDbus()
#
# def active_messeages(request):
#     texts = baulicht.list_text()
#     return render_to_response('active_list.html', {'texts': texts})


class MessageCreate(CreateView):
    model = Message
    fields = ["name", "email", "text"]
    template_name = "create.html"
    success_url = reverse_lazy('messages:queue')


class Queue(ListView):
    queryset = Message.objects.filter(accepted=False)
    template_name = "queue.html"
