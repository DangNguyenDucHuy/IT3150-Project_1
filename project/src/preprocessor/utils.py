import numpy as np
import matplotlib.pyplot as plt
import cv2
from cv2.typing import MatLike

from config import DEBUG


# NOTE: Used for EDA
def eda_check_frame_changed(
    cur_frame: MatLike, 
    last_frame: MatLike, 
    pixel_changed_threshold: int = 0,
):
    pixel_changes = cur_frame - last_frame
    pixel_diffs = pixel_changes != 0
    pixel_changed_count = np.sum(pixel_diffs)
    
    total_pixels = cur_frame.shape[0] * cur_frame.shape[1]
    
    # print(f"Shape: {cur_frame.shape[0] * cur_frame.shape[1]}")
    # print(f"Pixel changed count: {pixel_changed_count}")
    # print(f"Changed percent: {pixel_changed_count / total_pixels}")

    pixels_changed_amounts = [np.sum(pixel_changes == i) for i in range(256)]
    
    # fig, ax = plt.subplots()
    # ax.bar(list(range(256)), pixels_changed_amounts)
    # ax.boxplot(pixel_changes.flatten())
    
    # fig.savefig("D:/huy/DaiHoc/MonHoc/2026.1/IT3150 - Project I/project/docs/figures/eda-youtube_video-boxplot.png")
    # plt.show()
    
    import pandas as pd
    
    df = pd.DataFrame({ "x": list(range(256)), "y": pixels_changed_amounts })
    # print(df.describe())
    
    q3_change_threshold = df.quantile(q=0.75)
    q3_change_threshold = q3_change_threshold["x"]
    
    pixel_changed_exceed_q3_count = np.sum((pixel_changes > q3_change_threshold))
    pixel_changed_exceed_q3_percent = pixel_changed_exceed_q3_count / total_pixels
    # print(f"Pixel changed exceed Q3 count: {pixel_changed_exceed_q3_count}")
    # print(f"Changed exceed Q3 percent: {pixel_changed_exceed_q3_percent}")
    
    exceed_q3_pixels = (pixel_changes > q3_change_threshold) * 255
    
    # cv2.imwrite("D:/huy/DaiHoc/MonHoc/2026.1/IT3150 - Project I/project/docs/figures/eda-youtube_video-exceed_q3.png", exceed_q3_pixels.astype(np.uint8))
    
    # cv2.imshow("Exceed Q3 pixels", exceed_q3_pixels.astype(np.uint8))
    # cv2.waitKey(0)
    # cv2.destroyAllWindows()

    return pixel_changed_exceed_q3_percent
    return (pixel_changed_count / total_pixels)
    return (pixel_changed_count > pixel_changed_threshold)
