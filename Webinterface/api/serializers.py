from rest_framework import serializers

from main.models import Message

class MessageSerializer(serializers.ModelSerializer):
    class Meta:
        model = Message
        fields = ('name', 'email', 'text', 'created')


class ActiveMessageSerializer(serializers.Serializer):
    path = serializers.CharField(max_length=100)
    text = serializers.CharField(max_length=512)
