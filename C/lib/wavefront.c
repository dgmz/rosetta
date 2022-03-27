#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <errno.h>

#include "wavefront.h"

static int parse_vertex(const char *line, struct wf_vertex *v)
{
	int n;
	
	assert(v);
	v->w = 1.0;
	n = sscanf(line, " v %f %f %f %f", &v->x, &v->y, &v->z, &v->w);
	return 3 == n || 4 == n;
}

/*
static int parse_face(char *line, int *indices, int max_indices)
{
	int index;
	int i;
	
	assert(line);
	assert(indices);
	assert(max_indices);
	FILE *stream = NULL;
	i = 0;
	stream = fmemopen(line, strlen(line), "r");
	if (stream) {
		if (1 == fscanf(stream, " f %d", &index)) {
			indices[0] = index;
			fscanf(stream, "/%*s");
			for (i = 1; i < max_indices; i++) {
				if (fscanf(stream, " %d", &index) != 1) {
					break;
				}
				indices[i] = index;
				fscanf(stream, "/%*s");
			}
		}
		fclose(stream);
	}
	return i;
}

static int parse_face(char *line, struct wf_face *face)
{
	int index;
	int i;
	
	assert(line);
	assert(face);
	assert(!face->indices);
	assert(!face->nindices);
	FILE *stream = NULL;
	i = 0;
	stream = fmemopen(line, strlen(line), "r");
	if (stream) {
		int index[3];
		if (1 == fscanf(stream, " f %d %d %d", &index[0], &index[1], &index[2])) {
			int *indices = malloc(sizeof(int) * 3);
			if (!indices) {
				fclose(stream);
				return 0;
			}
			memcpy(indices, index, sizeof(index));
			face->indices = indices;
			face->nindices = 3;
			fscanf(stream, "/%*s");
			while (fscanf(stream, " %d", &index[0]) == 1) {
				indices = realloc(face->indices, sizeof(int) * (face->nindices + 1));
				if (!indices) {
					fclose(stream);
					return 0;
				}
				indices[face->nindices] = index[0];
				face->nindices++;
				fscanf(stream, "/%*s");
			}
		}
		fclose(stream);
	}
	return 1;
}
*/

static int parse_face(char *line, struct wf_face *face)
{
	return 0;
}

static int parse_line(char *line, struct wf_model *model)
{
	struct wf_vertex vertex;
	struct wf_face face;
	
	if (parse_vertex(line, &vertex)) {
		size_t new_size = (model->nvertices + 1) * sizeof(struct wf_vertex);
		struct wf_vertex *vertices = realloc(model->vertices, new_size);
		if (!vertices) {
			return 0;
		}
		memcpy(&vertices[model->nvertices], &vertex, sizeof(struct wf_vertex));
		model->vertices = vertices;
		model->nvertices++;
		return 1;
	}
	if (parse_face(line, &face)) {
		return 1;
	}
	return 0;
}

static struct wf_model *read_file(FILE *file)
{
	struct wf_model *model;
	char *line = NULL;
	size_t line_size = 0;
	
	model = calloc(1, sizeof(struct wf_model));
	if (!model) {
		return NULL;
	}
	while (-1 != getline(&line, &line_size, file)) {
		if (!parse_line(line, model) && errno) {
			perror("");
			wf_free(model);
			return NULL;
		}
	}
	model->nfaces = 2492; // FIXME
	model->faces = calloc(2492, sizeof(struct wf_face));
	model->faces[0].nindices = 3;
	model->faces[0].indices = calloc(3, sizeof(int));
	model->faces[0].indices[0] = 24;
	model->faces[0].indices[1] = 25;
	model->faces[0].indices[2] = 26;
	model->faces[2491].nindices = 3;
	model->faces[2491].indices = calloc(3, sizeof(int));
	model->faces[2491].indices[0] = 1201;
	model->faces[2491].indices[1] = 1202;
	model->faces[2491].indices[2] = 1200;
	
	return model;
}

struct wf_model *wf_read(const char *name)
{
	struct wf_model *model;
	assert(name);
	FILE *file = fopen(name, "r");
	if (!file) {
		return NULL;
	}
	model = read_file(file);
	fclose(file);
	return model;
}

void wf_free(struct wf_model *model)
{
	if (model) {
		free(model->vertices);
	}
	free(model);
}
