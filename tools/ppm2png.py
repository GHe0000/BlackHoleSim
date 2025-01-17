# 一个简单的 Python 脚本，用于将生成的 PPM 格式的图像转换为 PNG 格式。
# 使用方法：
# python ppm2png.py <input_ppm_path> <output_png_path>

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

if __name__ == "__main__":
    if len(sys.argv) != 3:
        print("Usage: python ppm2png.py <input_ppm_path> <output_png_path>")
    else:
        ppm_path = sys.argv[1]
        png_path = sys.argv[2]
        convert_ppm_to_png(ppm_path, png_path)
