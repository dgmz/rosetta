#!/usr/bin/python3

import tga

black = (0, 0, 0)
white = (255, 255, 255)
red = (255, 0, 0)

# new 100x100 black image
data = [
	[black for x in range(100)] for y in range(100)
]
data[10][41] = red # set pixel
data = data[::-1] # flip vertically

# save as TGA
image = tga.Image(data)
image.save("lesson00.tga")

print("DONE")