#include <stdio.h> // printf()
#include <stdlib.h> // abs()
#include <stdint.h>
#include <stdbool.h>
#include "lib/tga.h"

#define BLACK (0xFF000000)
#define WHITE (0xFFFFFFFF)
#define RED   (0xFFFF0000)
#define GREEN (0xFF00FF00)
#define BLUE  (0xFF0000FF)

#define WIDTH 100
#define HEIGHT 100

#define SWAP16(a,b) { uint16_t t = a; a = b; b = t; }

void line(uint32_t *pixels, uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint32_t color)
{
	bool steep = false;
	if (abs(x0 - x1) < abs(y0 - y1)) {
		SWAP16(x0, y0);
		SWAP16(x1, y1);
		steep = true;
	}
	if (x1 < x0) {
		SWAP16(x0, x1);
		SWAP16(y0, y1);
	}
	int dx = x1 - x0;
	int dy = y1 - y0;
	int error = 0;
	int errord = abs(dy) * 2;
	int y_step = (y0 < y1) ? 1 : -1;
	int y = y0;
	for (int x = x0; x < x1; x++) {
		if (steep) {
			pixels[x * WIDTH + y] = color;
		} else {
			pixels[y * WIDTH + x] = color;
		}
		error += errord;
		if (dx < error) {
			y += y_step;
			error -= 2 * dx;
		}
	}
}

int main(void)
{
	uint32_t data[WIDTH * HEIGHT];
	for (size_t i = 0; i < WIDTH * HEIGHT; i++) {
		data[i] = BLACK;
	}
	
	for (int i = 0; i < 1000*1000; i++) {
		line(data, 13, 20, 80, 40, WHITE);
		line(data, 20, 13, 40, 80, RED);
		line(data, 80, 40, 13, 20, BLUE);
	}
	
	tga_save("lesson01-4.tga", data, WIDTH, HEIGHT);
	printf("DONE\n");
	return 0;
}
