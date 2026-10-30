import os
import ast
import numpy as np
import pandas as pd
import cv2
from typing import Any

from config import (
    DEBUG, PRODUCTION_ENV, 
    DATA_BRONZE_YOUTUBE_METADATA_PATH,
    DATA_SILVER_VIDEOS_DIR,
    EXTRACT_FRAME_INTERVAL_SECONDS,
    FRAME_FILENAME_NUMBER_DIGITS,
)


def _extract_video_frames(
    video_id: str,
    video_name: str,
    video_path: str,
    frame_positions: list[tuple[int,int,int,int]],
    save_dir: str = ""
) -> list[dict[str, Any]]:
    cap = cv2.VideoCapture(video_path)
    if not cap.isOpened():
        if DEBUG:
            print(f"[Error] Can't open video of path: {video_path}")
        return
    
    
    # Setup output directory
    if save_dir:
        for fp_idx in range(len(frame_positions)):
            current_save_dir = os.path.join(save_dir, f"{video_name}_{fp_idx+1}")
            os.makedirs(current_save_dir, exist_ok=True)
        
    
    metadata_rows = []
    extracting_count = 0
    
    
    while True:
        ret, frame = cap.read()
        if not ret:
            break
        
        current_seconds = cap.get(cv2.CAP_PROP_POS_MSEC) / 1000.0
        
        
        # Extracting each interval
        if current_seconds < extracting_count * EXTRACT_FRAME_INTERVAL_SECONDS:
            continue
        
        extracting_count += 1
        
        
        # At current frame, check for each position 
        for fp_idx, fpos in enumerate(frame_positions):
            sx, ex, sy, ey = fpos
            focused_frame = frame[sy:ey, sx:ex]
            
            if save_dir:
                current_save_dir = os.path.join(save_dir, f"{video_name}_{fp_idx+1}")

                current_save_path = os.path.join(
                    current_save_dir, 
                    f"{extracting_count:0{FRAME_FILENAME_NUMBER_DIGITS}d}.png"
                )
                
                cv2.imwrite(current_save_path, focused_frame.astype(np.uint8))
                
                height, width, _ = focused_frame.shape
                
                metadata_rows.append({
                    "video_id": video_id,
                    "video_name": video_name,
                    "subframe_idx": fp_idx+1,
                    "interval_seconds": EXTRACT_FRAME_INTERVAL_SECONDS,
                    "resolution": (height, width),
                    "save_path": current_save_path,
                })

    
    cap.release()
    
    return metadata_rows

     
    
    
def video_preprocessor(
    input_path: str = DATA_BRONZE_YOUTUBE_METADATA_PATH,
    output_dir: str = DATA_SILVER_VIDEOS_DIR,
    save_data: bool = PRODUCTION_ENV,
) -> pd.DataFrame:
    # Read input (.csv)
    df = pd.read_csv(
        input_path,
        converters={
            "download_range_seconds": ast.literal_eval,
            "frame_positions": ast.literal_eval,
        }
    )
    
    # Metadata
    metadata_cols = [
        "video_id", "video_name", "subframe_idx", 
        "interval_seconds", "resolution", "save_path"
    ]
    metadata_rows = []
    
    
    for idx, row in df.iterrows():
        video_name = f"{row["video_id"]}_{row["download_range_idx"]}"
        
        # Validate
        if not row["save_path"]:
            if DEBUG:
                print(f"[Warning] Video {video_name} save path not found")
            continue

        if not row["frame_positions"]:
            if DEBUG:
                print(f"[Warning] Video {video_name} frame_positions not found")
            continue
        
        # Handle each video's download range
        current_metadata_rows = _extract_video_frames(
            video_id=row["video_id"],
            video_name=video_name,
            video_path=row["save_path"],
            frame_positions=row["frame_positions"],
            save_dir=output_dir,
        )
        
        metadata_rows.extend(current_metadata_rows)
        
    
    # Metadata
    metadata_df = pd.DataFrame(metadata_rows, columns=metadata_cols)
    
    if save_data:
        metadata_df.to_csv(os.path.join(output_dir, "metadata.csv"))

    return metadata_df
