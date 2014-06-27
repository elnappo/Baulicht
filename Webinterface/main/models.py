from datetime import datetime

from django.db import models
from pybaulicht import BaulichtDbus


bus = BaulichtDbus()

class Message(models.Model):
    created = models.DateTimeField(auto_now_add=True)
    created_ip = models.GenericIPAddressField(null=True)

    name = models.CharField(blank=True, max_length=32, default="")
    email = models.EmailField(blank=True, max_length=128, default="")
    text = models.TextField(max_length=512)

    dbus_path = models.CharField(blank=True, default="", max_length=32)
    accepted = models.NullBooleanField(null=True, default=None)
    is_active = models.NullBooleanField(null=True, default=None)
    activated_at = models.DateTimeField(null=True)

    def send_to_dbus(self):
        if not self.dbus_path:
            self.dbus_path = bus.add_text(self.text)
            self.activated_at = datetime.now()
            self.accepted = True
            self.is_active = True
            self.save()

    def remove_from_dbus(self):
        if self.dbus_path:
            bus.remove_text(self.dbus_path)
            self.is_active = False
            self.save()
