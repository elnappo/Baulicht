# -*- coding: utf-8 -*-
from django import forms

from main.models import Message


class MessageCreateForm(forms.ModelForm):
    class Meta:
        model = Message
        fields = ["name", "email", "text"]