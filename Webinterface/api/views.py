from rest_framework import generics
from rest_framework.views import APIView
from rest_framework.response import Response

from pybaulicht import BaulichtDbus

from main.models import Message
from api.serializers import MessageSerializer, ActiveMessageSerializer


baulicht = BaulichtDbus()

class QueueList(generics.ListCreateAPIView):
    queryset = Message.objects.filter(accepted=None)
    serializer_class = MessageSerializer


class ActiveList(APIView):
    def get(self, request, format=None):
        texts = baulicht.list_text()
        return Response(texts)
