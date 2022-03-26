#include <stdio.h>
#include <stdint.h>
#include "lib/tga.h"

#define BLACK (0xFF000000)
#define WHITE (0xFFFFFFFF)
#define RED   (0xFFFF0000)
#define GREEN (0xFF00FF00)
#define BLUE  (0xFF0000FF)

#define WIDTH 100
#define HEIGHT 100

void line(uint32_t *pixels, uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint32_t color)
{
	for (float t = 0; t < 1; t += 0.01) {
		int x = x0 + (x1 - x0) * t;
		int y = y0 + (y1 - y0) * t;
		pixels[y * WIDTH + x] = color;
	}
}

int main(void)
{
	uint32_t data[WIDTH * HEIGHT];
	for (size_t i = 0; i < WIDTH * HEIGHT; i++) {
		data[i] = BLACK;
	}
	
	line(data, 13, 20, 80, 40, WHITE);
	
	tga_save("lesson01-1.tga", data, WIDTH, HEIGHT);
	printf("DONE\n");
	return 0;
}
