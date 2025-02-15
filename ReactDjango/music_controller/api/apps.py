from django.apps import AppConfig
from .backend.helpers import *
import os


class ApiConfig(AppConfig):
    default_auto_field = 'django.db.models.BigAutoField'
    name = 'api'
    def ready(self):
        # This only runs once when the server starts
        if os.environ.get('RUN_MAIN'):
            printHelloWorld()
