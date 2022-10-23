#!/usr/bin/python3

import tga
import wavefront

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
	derror = abs(dy / dx) if dx else 1
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

WIDTH = 800
HEIGHT = 800
# new 100x100 black image
data = [
	[black for x in range(WIDTH)] for y in range(HEIGHT)
]
model = wavefront.load_obj('african_head.obj')
for face in model.polygons:
	#print("face: " + str(model.polygons.index(face)))
	for j in range(3):
		i0 = face[j][0]
		i1 = face[(j + 1) % 3][0]
		v0 = model.vertices[i0]
		v1 = model.vertices[i1]
		x0 = (v0[0] + 1) * (WIDTH - 1) / 2
		y0 = (v0[1] + 1) * (HEIGHT - 1) / 2
		x1 = (v1[0] + 1) * (WIDTH - 1) / 2
		y1 = (v1[1] + 1) * (HEIGHT - 1) / 2
		#print(f"{i0}-{i1} ({x0},{y0})-({x1},{y1})")
		line(data, int(x0), int(y0), int(x1), int(y1), white)

data = data[::-1] # flip vertically
# save as TGA
image = tga.Image(data)
image.save("lesson01-6.tga")

print("DONE")
