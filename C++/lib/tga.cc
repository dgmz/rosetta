#include <stdint.h>
#include <assert.h>
#include <unistd.h> // write()
#include <fcntl.h> // open()

#include "tga.h"

static int _save_fd(int fd, const uint32_t *pixels, uint16_t width, uint16_t height)
{
	uint32_t num_pixels = width * height;
	char header[18] = {0};
	
	header[2] = 2; // truecolor
	header[12] = width & 0xFF;
	header[13] = (width >> 8) & 0xFF;
	header[14] = height & 0xFF;
	header[15] = (height >> 8) & 0xFF;
	header[16] = 32; // RGBA
	//header[17] = 8; // for TGA-32

	if (sizeof(header) != write(fd, &header, sizeof(header))) {
		return 0;
	}
	// otherwise we may overflow below
	assert(sizeof(uint32_t) < sizeof(size_t));
	if (4 * num_pixels != write(fd, pixels, 4 * num_pixels)) {
		return 0;
	}
	return 1; 
}

int tga_save(const char *name, const uint32_t *pixels, uint16_t width, uint16_t height)
{
	int fd = -1;
	int res;
	
	assert(name);
	assert(pixels);
	assert(width);
	assert(height);
	
	fd = creat(name, 0644);
	if (-1 == fd) {
		return 0;
	}
	res = _save_fd(fd, pixels, width, height);
	close(fd);
	return res;
}
