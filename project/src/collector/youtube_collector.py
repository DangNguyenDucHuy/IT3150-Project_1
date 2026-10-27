import os
import time
import pandas as pd
from yt_dlp import YoutubeDL

from config import DEBUG, PRODUCTION_ENV, DATA_SOURCES_YOUTUBE_VIDEOS_PATH, DATA_BRONZE_YOUTUBE_DIR, YTDLP_OPTIONS
from .utils import normalize_title, generate_youtube_url_from_id, extract_ytdlp_info_fields


def youtube_collector(
    input_path: str = DATA_SOURCES_YOUTUBE_VIDEOS_PATH,
    output_dir: str = DATA_BRONZE_YOUTUBE_DIR,
    save_data: bool = PRODUCTION_ENV,
) -> pd.DataFrame:
    # Read input
    df = pd.read_csv(input_path)
    
    # Output filename format: <video_id>.<ext>
    ytdlp_options = YTDLP_OPTIONS
    ytdlp_options["outtmpl"] = os.path.join(output_dir, "%(id)s.%(ext)s")
    
    # Download videos
    for idx, row in df.iterrows():
        video_id = row.get("video_id")
        if video_id is None:
            if DEBUG:
                print(f"[Error] At row {idx}: video_id not found")
            continue
        
        video_url = generate_youtube_url_from_id(video_id=video_id)
        
        save_path = ""
        elapsed_time = 0.0
        
        with YoutubeDL(ytdlp_options) as ydl:
            download_start_time = time.monotonic()
            
            info = ydl.extract_info(video_url, download=False)
            
            if save_data:
                elapsed_time = time.monotonic() - download_start_time
            
            extracted_info = extract_ytdlp_info_fields(info)

            if save_data:
                save_path = os.path.join(output_dir, f"{extracted_info["video_id"]}.{extracted_info["video_ext"]}")
        
        # Metadata
        df.at[idx, "video_url"] = video_url
        df.at[idx, "title"] = extracted_info["title"]
        df.at[idx, "normalized_title"] = normalize_title(extracted_info["title"])
        df.at[idx, "filesize_bytes"] = extracted_info["filesize_bytes"]
        df.at[idx, "duration_seconds"] = extracted_info["duration_seconds"]
        df.at[idx, "fps"] = extracted_info["fps"]
        df.at[idx, "resolution"] = extracted_info["height"]
        df.at[idx, "uploaded_date"] = extracted_info["uploaded_date"]
        df.at[idx, "creator"] = extracted_info["creator"]
        df.at[idx, "video_ext"] = extracted_info["video_ext"]
        df.at[idx, "download_time_seconds"] = elapsed_time
        df.at[idx, "save_path"] = save_path

        if DEBUG:
            print(f"[Info] ID: {row["video_id"]} - Download time: {elapsed_time}")
            
            # NOTE: Download only 1 video for quick testing
            # TODO: Remove this to download all videos later
            break
    
    # Save metadata
    if save_data:
        df.to_csv(os.path.join(output_dir, f"metadata.csv"))
    
    return df
