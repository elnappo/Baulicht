from django.conf.urls import patterns, url
from django.contrib.auth.decorators import login_required

from main.views import MessageCreate, MessageList

urlpatterns = patterns('',
    # Examples:
    # url(r'^$', 'glimpse.views.home', name='home'),
    # url(r'^blog/', include('blog.urls')),

    url(r'^create/$', MessageCreate.as_view(), name='create'),
    url(r'^list/$', MessageList.as_view(), name='list'),
)