# 一个批量将 PPM 格式图像转换为 PNG 格式图像的脚本。
# 使用方法：
# python batch_ppm2png.py <ppm_folder_path> <png_folder_path>

import os
import sys
from PIL import Image

def convert_ppm_to_png(ppm_path, png_path):
    try:
        # 打开 PPM 文件
        with Image.open(ppm_path) as img:
            # 将图像保存为 PNG 格式
            img.save(png_path, 'PNG')
        print(f"Successfully converted {ppm_path} to {png_path}")
    except Exception as e:
        print(f"An error occurred: {e}")

if __name__ == '__main__':
    # 从命令行读取文件夹路径
    if len(sys.argv) != 3:
        print(f"Usage: python {sys.argv[0]} <ppm_folder_path> <png_folder_path>")
        sys.exit(1)
    ppm_folder_path = sys.argv[1]
    png_folder_path = sys.argv[2]
    # 遍历 PPM 文件夹
    for ppm_file in os.listdir(ppm_folder_path):
        # 构造 PPM 文件路径
        ppm_file_path = os.path.join(ppm_folder_path, ppm_file)
        # 构造 PNG 文件路径
        png_file_path = os.path.join(png_folder_path, ppm_file.replace('.ppm', '.png'))
        # 转换 PPM 文件为 PNG 文件
        convert_ppm_to_png(ppm_file_path, png_file_path)
        print(f"Converted {ppm_file_path} to {png_file_path}")
    print(f"All PPM files in {ppm_folder_path} have been converted to PNG format and saved to {png_folder_path}")
