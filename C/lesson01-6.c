#include <stdio.h> // printf()
#include <stdlib.h> // abs()
#include <stdint.h>
#include <stdbool.h>
#include "lib/tga.h"
#include "lib/wavefront.h"

#define BLACK (0xFF000000)
#define WHITE (0xFFFFFFFF)
#define RED   (0xFFFF0000)
#define GREEN (0xFF00FF00)
#define BLUE  (0xFF0000FF)

#define WIDTH 800
#define HEIGHT 800

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
	
	/*
	model = wavefront.load_obj('african_head.obj')
	*/
	struct wf_model *model = NULL;
	model = wf_read("african_head.obj");

	/*
	for face in model.polygons:
	*/
	for (int i = 0; i < model->nfaces; i++) {
		//printf("face: %d\n", i);
		if (3 != model->faces[i].nindices) {
			printf("wrong number of vertices\n");
			continue;
		}
		/*
		for j in range(3):
		*/
		for (int j = 0; j < 3; j++) {
			/*
			v0 = model.vertices[face[j][0]]
			v1 = model.vertices[face[(j + 1) % 3][0]]
			x0 = (v0[0] + 1) * (WIDTH - 1) / 2
			y0 = (v0[1] + 1) * (HEIGHT - 1) / 2
			x1 = (v1[0] + 1) * (WIDTH - 1) / 2
			y1 = (v1[1] + 1) * (HEIGHT - 1) / 2
			*/ 
			int v0, v1;
			float x0, x1, y0, y1;
			v0 = model->faces[i].indices[j] - 1;
			v1 = model->faces[i].indices[(j + 1) % 3] - 1;
			//printf ("%d-%d ", v0, v1);
			x0 = (model->vertices[v0].x + 1) * (WIDTH - 1) / 2;
			y0 = (model->vertices[v0].y + 1) * (HEIGHT - 1) / 2;
			x1 = (model->vertices[v1].x + 1) * (WIDTH - 1) / 2;
			y1 = (model->vertices[v1].y + 1) * (HEIGHT - 1) / 2;
			//printf("(%f,%f)-(%f,%f)\n", x0, y0, x1, y1);
			/*
			line(data, int(x0), int(y0), int(x1), int(y1), white)
			*/ 
			line(data, x0, y0, x1, y1, WHITE);
		}
	}

	/*
	image = tga.Image(data)
	image.save("lesson01-6.tga")
	*/
	tga_save("lesson01-6.tga", data, WIDTH, HEIGHT);
	
	printf("DONE\n");
	return 0;
}
