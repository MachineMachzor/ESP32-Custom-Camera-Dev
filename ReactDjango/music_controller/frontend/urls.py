from django.urls import path
from .views import index
# from api.views import main

from django.conf import settings
from django.conf.urls.static import static

urlpatterns = [
    path('', index),
    path('join', index),
    path('create', index),
    path('room/<str:roomCode>', index)
    # path('', main)
]

if settings.DEBUG:
    urlpatterns += static(settings.STATIC_URL, document_root=settings.STATIC_ROOT)


