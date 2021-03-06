from django.conf.urls import patterns, include, url
from django.views.generic import TemplateView

from django.contrib import admin


admin.autodiscover()

urlpatterns = patterns('',
    # Examples:
    # url(r'^$', 'Webinterface.views.home', name='home'),
    # url(r'^blog/', include('blog.urls')),

    url(r'^admin/', include(admin.site.urls)),
    url(r'^$', TemplateView.as_view(template_name='index.html'), name='index'),
    url(r'^messages/', include('main.urls', 'messages')),
    url(r'^api/', include('api.urls', 'api')),
)
