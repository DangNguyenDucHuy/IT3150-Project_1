import os
import time
import ast
import pandas as pd
from yt_dlp import YoutubeDL
from yt_dlp.utils import download_range_func

from config import (
    DEBUG, PRODUCTION_ENV, 
    DATA_SOURCES_YOUTUBE_VIDEOS_PATH, DATA_BRONZE_YOUTUBE_DIR, 
    YTDLP_OPTIONS
)
from .utils import normalize_title, generate_youtube_url_from_id, extract_ytdlp_info_fields


def youtube_collector(
    input_path: str = DATA_SOURCES_YOUTUBE_VIDEOS_PATH,
    output_dir: str = DATA_BRONZE_YOUTUBE_DIR,
    save_data: bool = PRODUCTION_ENV,
) -> pd.DataFrame:
    # Read input
    df = pd.read_csv(
        input_path,
        converters={
            "download_ranges_seconds": ast.literal_eval,
            "frame_positions": ast.literal_eval,
        }
    )
    
    # yt-dlp general options
    ytdlp_options = YTDLP_OPTIONS
    ytdlp_options["force_keyframes_at_cuts"] = True
    
    # Metadata 
    metadata_cols = [
        "video_id", "video_url", "title", "normalized_title", 
        "filesize_bytes", "fps", "resolution", "duration_seconds", 
        "uploaded_date", "creator", "video_ext", 
        "download_range_seconds", "download_range_idx", "frame_positions", 
        "download_time_seconds", "save_path"
    ]
    metadata_rows = []
    
    
    # Download videos
    for idx, row in df.iterrows():
        video_id = row.get("video_id")
        if video_id is None:
            if DEBUG:
                print(f"[Error] At row {idx}: video_id not found")
            continue
        
        video_url = generate_youtube_url_from_id(video_id=video_id)
        
        video_part_idx = 0
        
        # Download sepecific ranges
        for drange, fpos in zip(df.loc[idx, "download_ranges_seconds"], df.loc[idx, "frame_positions"]):
            save_path = ""
            elapsed_time = 0.0
            video_part_idx += 1
        
            ytdlp_options["download_ranges"] = download_range_func(None, ranges=[drange])
            ytdlp_options["outtmpl"] = os.path.join(output_dir, f"%(id)s_{video_part_idx}.%(ext)s")
            
        
            with YoutubeDL(ytdlp_options) as ydl:
                download_start_time = time.monotonic()
                
                info = ydl.extract_info(video_url, download=save_data)
                
                if save_data:
                    elapsed_time = time.monotonic() - download_start_time
                
                extracted_info = extract_ytdlp_info_fields(info)

                if save_data:
                    save_path = os.path.join(
                        output_dir, 
                        f"{extracted_info["video_id"]}_{video_part_idx}.{extracted_info["video_ext"]}"
                    )

            # Metadata
            metadata_rows.append({
                "video_id": video_id,
                "video_url": video_url,
                "title": extracted_info["title"],
                "normalized_title": normalize_title(extracted_info["title"]),
                "filesize_bytes": extracted_info["filesize_bytes"],
                "fps": extracted_info["fps"],
                "resolution": extracted_info["height"],
                "duration_seconds": extracted_info["duration_seconds"],
                "uploaded_date": extracted_info["uploaded_date"],
                "creator": extracted_info["creator"],
                "video_ext": extracted_info["video_ext"],
                "download_range_seconds": drange,
                "download_range_idx": video_part_idx,
                "frame_positions": fpos,
                "download_time_seconds": elapsed_time,
                "save_path": save_path,
            })

        
        if DEBUG:
            print(f"[Info] ID: {row["video_id"]} - Download time: {elapsed_time}")
            
            # NOTE: Download only 1 video for quick testing
            # TODO: Remove this to download all videos later
            break
    
    
    # Metadata
    metadata_df = pd.DataFrame(metadata_rows, columns=metadata_cols)
    
    if save_data:
        metadata_df.to_csv(os.path.join(output_dir, f"metadata.csv"))
    
    return metadata_df
