from django.conf.urls import url, patterns, include

from api.views import QueueList


urlpatterns = patterns('',
    url(r'^queue/$', QueueList.as_view(), name='queue-list'),
    url(r'^api-auth/', include('rest_framework.urls', namespace='rest_framework'))
)
