import os
from dotenv import load_dotenv

load_dotenv()


# === Environment variables

DEBUG = (os.getenv("DEBUG").lower() == "true")
PRODUCTION_ENV = (os.getenv("PRODUCTION_ENV").lower() == "true")
FFMPEG_PATH = os.getenv("FFMPEG_PATH")
YTDLP_VIDEO_RESOLUTION = int(os.getenv("YTDLP_VIDEO_RESOLUTION") or 720)



# === Directories and paths

# NOTE: Define absolute Current Working Directory path by using relative path: ../../../project
CWD = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

# Folder lv1
DATA_DIR = os.path.join(CWD, "data")

# Folder lv2
DATA_SOURCES_DIR = os.path.join(DATA_DIR, "sources")
DATA_BRONZE_DIR = os.path.join(DATA_DIR, "bronze")

# Folder lv3
DATA_BRONZE_YOUTUBE_DIR = os.path.join(DATA_BRONZE_DIR, "youtube")



