from django.db import models


class Message(models.Model):
    created = models.DateTimeField(auto_now_add=True)
    created_ip = models.GenericIPAddressField(null=True)

    name = models.CharField(blank=True, max_length=32)
    email = models.EmailField(blank=True, max_length=128)
    text = models.TextField(max_length=512)

    dbus_path = models.CharField(blank=True, default="", max_length=32)

    in_queue = models.BooleanField(default=True)
    accepted = models.BooleanField(default=False)
    accepted_at = models.DateTimeField(null=True)
    is_active = models.BooleanField(default=False)
