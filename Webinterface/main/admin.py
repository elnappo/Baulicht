from django.contrib import admin

from main.models import Message


def to_dbus(modeladmin, request, queryset):
    for message in queryset:
        message.send_to_dbus()

to_dbus.short_description = "Mark selected messages as published"


def remove_from_dbus(modeladmin, request, queryset):
    for message in queryset:
        message.remove_from_dbus()

remove_from_dbus.short_description = "Mark selected messages as published"


class MessageAdmin(admin.ModelAdmin):
    list_display = ("name", "text", "accepted", "is_active")
    list_display_links = ("name", "text")

    list_filter = ("name", "email", "accepted", "is_active", "created", )

    actions = [to_dbus, remove_from_dbus()]

# Register your models here.
admin.site.register(Message, MessageAdmin)
