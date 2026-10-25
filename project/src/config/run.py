import os

from .main import (
    DEBUG, FFMPEG_PATH,
    CWD, DATA_DIR, DATA_SOURCES_DIR, DATA_BRONZE_DIR,
    DATA_BRONZE_YOUTUBE_DIR,
)



def setup_config():
    # Root folder - current working directory
    os.makedirs(CWD, exist_ok=True)

    # Folder lv1
    os.makedirs(DATA_DIR, exist_ok=True)

    # Folder lv2
    os.makedirs(DATA_SOURCES_DIR, exist_ok=True)
    os.makedirs(DATA_BRONZE_DIR, exist_ok=True)
    
    # Folder lv3
    os.makedirs(DATA_BRONZE_YOUTUBE_DIR, exist_ok=True)

    
    if DEBUG:
        print("[Info] Folders setup")
    
    
    if DEBUG:
        if FFMPEG_PATH is None:
            print("[Warning] FFMPEG_PATH isn't found in .env")



if __name__ == "__main__":
    setup_config()
