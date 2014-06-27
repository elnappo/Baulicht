from django.conf.urls import url, patterns, include

from api.views import QueueList, ActiveList


urlpatterns = patterns('',
    url(r'^queue/$', QueueList.as_view(), name='queue-list'),
    url(r'^active/$', ActiveList.as_view(), name='active-list'),
    url(r'^api-auth/', include('rest_framework.urls', namespace='rest_framework'))
)
