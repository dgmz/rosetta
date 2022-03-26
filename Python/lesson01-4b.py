#!/usr/bin/python3

import tga

black = (0, 0, 0)
white = (255, 255, 255)
red = (255, 0, 0)
green = (0, 255, 0)
blue = (0, 0, 255)

def line(buffer, x0, y0, x1, y1, color):
	steep = False
	if abs(x0 - x1) < abs(y0 - y1):
		x0, y0 = y0, x0
		x1, y1 = y1, x1
		steep = True
	if x0 > x1:
		x0, x1 = x1, x0
		y0, y1 = y1, y0
	dx = x1 - x0
	dy = y1 - y0
	sy = 1 if y0 < y1 else -1
	derror = abs(dy / dx)
	error = 0
	y = y0
	if steep:
		for x in range(x0, x1):
			buffer[int(x)][int(y)] = color
			error += derror
			if 0.5 < error:
				y += sy
				error -= 1
	else:
		for x in range(x0, x1):
			buffer[int(y)][int(x)] = color
			error += derror
			if 0.5 < error:
				y += sy
				error -= 1

# new 100x100 black image
data = [
	[black for x in range(100)] for y in range(100)
]

for n in range(1000*1000):
	line(data, 13, 20, 80, 40, white)
	line(data, 20, 13, 40, 80, red)
	line(data, 80, 0, 13, 20, blue)

data = data[::-1] # flip vertically
# save as TGA
image = tga.Image(data)
image.save("lesson01-4.tga")

print("DONE")