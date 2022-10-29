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

int main(void)
{
	uint32_t data[WIDTH * HEIGHT];
	for (size_t i = 0; i < WIDTH * HEIGHT; i++) {
		data[i] = BLACK;
	}
	data[10 + 41 * WIDTH] = RED;
	
	tga_save("lesson00.tga", data, WIDTH, HEIGHT);
	printf("DONE\n");
	return 0;
}
