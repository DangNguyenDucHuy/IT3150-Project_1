from config import PRODUCTION_ENV
from .youtube_collector import youtube_collector

def run_collector():
    youtube_collector(save_data=PRODUCTION_ENV)


if __name__ == "__main__":
    run_collector()
