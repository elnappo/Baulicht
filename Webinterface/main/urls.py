from django.conf.urls import patterns, url
from django.contrib.auth.decorators import login_required

from main.views import MessageCreate, Queue


urlpatterns = patterns('',
    # Examples:
    # url(r'^$', 'glimpse.views.home', name='home'),
    # url(r'^blog/', include('blog.urls')),

    url(r'^create/$', MessageCreate.as_view(), name='create'),
    url(r'^queue/$', Queue.as_view(), name='queue'),
    url(r'^active$', 'main.views.active_messeages', name='active'),
    url(r'^active$', Queue.as_view(), name='active'),
)