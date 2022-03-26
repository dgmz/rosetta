#!/usr/bin/python3

import tga

black = (0, 0, 0)
white = (255, 255, 255)
red = (255, 0, 0)

def frange(start, end, step):
	count = int((end - start) / step)
	for i in range(count):
		yield start + i * step

def line(buffer, x0, y0, x1, y1, color):
	for t in frange(0, 1, 0.01):
		x = x0 + (x1 - x0) * t
		y = y0 + (y1 - y0) * t
		buffer[int(y)][int(x)] = color

# new 100x100 black image
data = [
	[black for x in range(100)] for y in range(100)
]

line(data, 10, 20, 80, 40, white)

data = data[::-1] # flip vertically
# save as TGA
image = tga.Image(data)
image.save("lesson01-1.tga")

print("DONE")