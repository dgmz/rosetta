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
	derror2 = int(abs(dy) * 2)
	error2 = 0
	y = y0
	dx2 = int(dx * 2)
	for x in range(x0, x1):
		if steep:
			buffer[x][y] = color
		else:
			buffer[y][x] = color
		error2 += derror2
		if dx < error2:
			y += sy
			error2 -= dx2

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
image.save("lesson01-5.tga")

print("DONE")