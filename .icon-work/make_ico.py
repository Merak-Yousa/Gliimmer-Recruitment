# -*- coding: utf-8 -*-
"""改进版：透明像素的 RGB 填白，避免缩放时出现黑边；并生成深色背景对照预览"""
from PIL import Image, ImageDraw, ImageFilter
import numpy as np, os
from collections import deque

SRC = r"C:\Users\19991\Desktop\Gliimmer-Recruitment\.icon-work\source.jpg"
OUT_DIR = r"C:\Users\19991\Desktop\Gliimmer-Recruitment\.icon-work"

im = Image.open(SRC).convert("RGB")
arr = np.asarray(im).astype(np.int16)
whiteish = (arr[:, :, 0] >= 240) & (arr[:, :, 1] >= 240) & (arr[:, :, 2] >= 240)

H, W = whiteish.shape
outside = np.zeros((H, W), dtype=bool)
dq = deque()
for x in range(W):
    for y in (0, H - 1):
        if whiteish[y, x] and not outside[y, x]:
            outside[y, x] = True; dq.append((y, x))
for y in range(H):
    for x in (0, W - 1):
        if whiteish[y, x] and not outside[y, x]:
            outside[y, x] = True; dq.append((y, x))
while dq:
    y, x = dq.popleft()
    for dy, dx in ((1, 0), (-1, 0), (0, 1), (0, -1)):
        ny, nx = y + dy, x + dx
        if 0 <= ny < H and 0 <= nx < W and whiteish[ny, nx] and not outside[ny, nx]:
            outside[ny, nx] = True; dq.append((ny, nx))

alpha = np.where(outside, 0, 255).astype(np.uint8)
a_img = Image.fromarray(alpha).filter(ImageFilter.MinFilter(3)).filter(ImageFilter.GaussianBlur(0.8))
alpha = np.asarray(a_img).copy()
rgb = np.asarray(im).copy()
# 全透明处填白，缩放时边缘只会变亮不会发黑
rgb[alpha == 0] = (255, 255, 255)
out = Image.fromarray(np.dstack([rgb, alpha]), "RGBA")

content = out.crop(out.getbbox())
cw, ch = content.size
side = int(max(cw, ch) / 0.94)
canvas = Image.new("RGBA", (side, side), (0, 0, 0, 0))
canvas.paste(content, ((side - cw) // 2, (side - ch) // 2), content)

master = canvas.resize((1024, 1024), Image.LANCZOS)
master.save(os.path.join(OUT_DIR, "icon_preview.png"))

sizes = [(256, 256), (128, 128), (96, 96), (64, 64), (48, 48), (40, 40), (32, 32), (24, 24), (20, 20), (16, 16)]
ico_path = os.path.join(OUT_DIR, "蓝色大肥鱼.ico")
master.save(ico_path, format="ICO", sizes=sizes)

frames = {s: master.resize((s, s), Image.LANCZOS) for s in (16, 24, 32, 48, 64, 128, 256)}
sheet = Image.new("RGBA", (900, 330), (32, 33, 40, 255))
x = 20
for s in (16, 24, 32, 48, 64, 128, 256):
    f = frames[s]
    sheet.paste(f, (x, 40), f)
    d = ImageDraw.Draw(sheet)
    d.text((x, 20), str(s), fill=(200, 200, 210, 255))
    x += s + 24
sheet.save(os.path.join(OUT_DIR, "contact_dark.png"))

print("content", content.size, "canvas", canvas.size)
print("ico", os.path.getsize(ico_path))
