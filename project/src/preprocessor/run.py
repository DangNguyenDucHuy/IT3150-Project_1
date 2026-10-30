from config import PRODUCTION_ENV
from .video_preprocessor import video_preprocessor

def run_preprocessor():
    video_preprocessor(save_data=PRODUCTION_ENV)


if __name__ == "__main__":
    run_preprocessor()
