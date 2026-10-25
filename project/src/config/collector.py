import os
from datetime import datetime
from typing import TypedDict
from .main import (
    DEBUG,
    FFMPEG_PATH,
    DATA_SOURCES_DIR,
    DATA_BRONZE_YOUTUBE_DIR,
    YTDLP_VIDEO_RESOLUTION,
)



DATA_SOURCES_YOUTUBE_VIDEOS_PATH = os.path.join(DATA_SOURCES_DIR, "youtube_videos.csv")
DATA_BRONZE_YOUTUBE_METADATA_PATH = os.path.join(DATA_BRONZE_YOUTUBE_DIR, "metadata.csv")

YTDLP_OPTIONS = {
    "format": f"bestvideo[height<={YTDLP_VIDEO_RESOLUTION}]",
    "ffmpeg_location": FFMPEG_PATH,
    "outtmpl": os.path.join(DATA_BRONZE_YOUTUBE_DIR, "%(id)s.%(ext)s"),
    "quiet": (not DEBUG),
    "noplaylist": True,
}

class YtdlpInfoSchema(TypedDict):
    video_id: str = None
    title: str = None
    fps: int = None
    height: int = None
    width: int = None
    video_ext: str = None
    duration_seconds: int = None
    filesize_bytes: int = None
    creator: str = None
    uploaded_date: datetime = None
