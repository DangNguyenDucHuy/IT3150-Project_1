import re
import unicodedata
from datetime import datetime
from typing import Any

from config import DEBUG, YtdlpInfoSchema


def normalize_vietnamese(text: str) -> str:
    """Lower text and remove Vietnamese accents"""
    text = text.lower().replace("đ", "d")
    text = unicodedata.normalize("NFD", text)
    text = "".join(
        char for char in text
        if unicodedata.category(char) != "Mn"
    )
    return text


def normalize_title(text: str) -> str:
    """Normalize Vietnamese then replace special characters by underscore '_'"""
    text = normalize_vietnamese(text)
    text = re.sub(r"[^a-z0-9]", "_", text)
    text = re.sub(r"_+", "_", text).strip("_")
    return text


def generate_youtube_url_from_id(video_id: str) -> str:
    """e.g. abc --> https://www.youtube.com/watch?v=abc"""
    return "https://www.youtube.com/watch?v=" + video_id



def extract_ytdlp_info_fields(info: dict[str, Any]) -> YtdlpInfoSchema:
    extracted_info = {}
    
    video_id = info.get("id")
    title = info.get("title") or info.get("fulltitle")
    fps = info.get("fps")
    
    height = info.get("height")
    width = info.get("width")
    resolution = info.get("resolution")
    aspect_ratio = info.get("aspect_ratio")

    if height is None:
        if resolution is not None:
            if isinstance(resolution, str):
                height = resolution.split("x")[-1]
            elif isinstance(resolution, int):
                height = resolution
            else:
                if DEBUG:
                    print(f"[Warning] Failed to get height (wrong resolution type: {type(resolution)})")
        elif (aspect_ratio is not None) and (width is not None):
            height = int(width / aspect_ratio)
        else:
            if DEBUG:
                print(f"[Warning] Failed to get height (width: {type(width)} = {width}, ratio: {type(aspect_ratio)} = {aspect_ratio})")
    
    if width is None:
        if (aspect_ratio is not None) and (height is not None):
            width = int(height * aspect_ratio)
    
    video_ext = info.get("ext")

    duration_seconds = info.get("duration")
    if duration_seconds is None:
        duration_str = info.get("duration_string")
        if isinstance(duration_str, str):
            splitted_durations = duration_str.split(":")[::-1]
            splitted_seconds = [
                int(d) * pow(60, idx)
                for idx, d 
                in enumerate(splitted_durations)
            ]
            duration_seconds = sum(splitted_seconds)
        else:
            if DEBUG:
                print(f"[Warning] Failed to get duration (wrong type of duration string: {type(duration_str)})")
    
    filesize_bytes = info.get("filesize")
    if filesize_bytes is None:
        approximated_filesize = info.get("filesize_approx")
        if isinstance(approximated_filesize, int):
            filesize_bytes = approximated_filesize
        else:
            if DEBUG:
                print(f"[Warning] Failed to get filesize (wrong type of approx filesize: {type(approximated_filesize)})")
    
    creator = info.get("uploader_id") or info.get("uploader")
    
    uploaded_date = info.get("upload_date")
    if isinstance(uploaded_date, str):
        try:
            uploaded_date = datetime.strptime(uploaded_date, "%Y%m%d")
        except ValueError:
            if DEBUG:
                print(f"[Warning] Failed to get uploaded_date (wrong date format, expected: {uploaded_date})")
    else:
        if DEBUG:
            print(f"[Warning] Failed to get uploaded_date (wrong type of uploaded_date: {type(uploaded_date)})")
    
    
    extracted_info = {
        "video_id": video_id,
        "title": title,
        "fps": fps,
        "height": height,
        "width": width,
        "video_ext": video_ext,
        "duration_seconds": duration_seconds,
        "filesize_bytes": filesize_bytes,
        "creator": creator,
        "uploaded_date": uploaded_date,
    }
    
    return extracted_info
