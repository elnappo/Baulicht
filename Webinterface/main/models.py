from django.db import models


class Message(models.Model):
    created = models.DateTimeField(auto_now_add=True)
    created_ip = models.GenericIPAddressField(null=True)

    name = models.CharField(blank=True, max_length=32)
    email = models.EmailField(blank=True, max_length=64)
    text = models.TextField(max_length=512)

    dbus_path = models.CharField(blank=True, default="", max_length=32)
    is_active = models.NullBooleanField(null=True, default=None)
    activated_at = models.DateTimeField(null=True)
