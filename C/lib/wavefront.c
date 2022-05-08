#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <errno.h>
//#include <ctype.h>
#include <math.h>

#include "wavefront.h"

static int isspace(char c)
{
	return ' ' == c || '\t' == c;
}

static void skip_space(const char **s)
{
	assert(s);
	while (isspace(**s)) {
		(*s)++;
	}
}

static double read_double(const char **s)
{
	char next = **s;
	if ('\r' != next && '\n' != next && '\0' != next) {
		double d = strtod(*s, (char **)s);
		if (ERANGE != errno) {
			next = **s;
			if (' ' == next || '\t' == next || '\0' == next || '\r' == next || '\n' == next) {
				return d;
			}
		}
		errno = 0;
	}
	return NAN;
}

static int parse_vertex(const char *line, struct wf_vertex *v)
{
	double r;
	assert(line);
	assert(v);
	
	r = read_double(&line);
	if (isnan(r)) {
		return 0;
	}
	v->x = r;
	r = read_double(&line);
	if (isnan(r)) {
		return 0;
	}
	v->y = r;
	r = read_double(&line);
	if (isnan(r)) {
		return 0;
	}
	v->z = r;
	r = read_double(&line);
	if (isnan(r)) {
		v->w = 1.0;
	} else {
		v->w = r;
	}
	return 1;
}

static int parse_face_index(const char **line, struct wf_face *face)
{
	long l;
	int *indices;
	char next;
	
	assert(line);
	assert(face);
	
	next = (**line);
	if ('\r' == next || '\n' == next || '\0' == next) {
		return 0;
	}
	l = strtol(*line, (char **)line, 10);
	if (ERANGE != errno) {
		if (l == (int)l) {
			indices = realloc(face->indices, (face->nindices + 1) * sizeof(int));
			if (indices) {
				indices[face->nindices] = (int)l;
				face->indices = indices;
				face->nindices++;
				next = (**line);
				if ('/' == next) {
					strtol((*line) + 1, (char **)line, 10);
				}
				next = (**line);
				if ('/' == next) {
					strtol((*line) + 1, (char **)line, 10);
				}
				return 1;
			}
		}
	}
	errno = 0;
	return 0;
}

static int parse_face(const char *line, struct wf_face *face)
{
	assert(line);
	assert(face);
	
	while (parse_face_index(&line, face)) {
	}
	if ('\r' == *line || '\n' == *line || '\0' == *line || 2 < face->nindices) {
		return 1;
	}
	return 0;
}

static int parse_line(const char *line, struct wf_model *model)
{
	assert(line);
	assert(model);
	
	size_t new_size;
	
	skip_space(&line);
	if ('v' == *line) {
		new_size = (model->nvertices + 1) * sizeof(struct wf_vertex);
		struct wf_vertex *vertices = realloc(model->vertices, new_size);
		if (!vertices) {
			return 0;
		}
		memset(&vertices[model->nvertices], 0, sizeof(struct wf_vertex));
		if (parse_vertex(line+1, &vertices[model->nvertices])) {
			model->vertices = vertices;
			model->nvertices++;
			return 1;
		}
	} else if ('f' == *line) {
		new_size = (model->nfaces + 1) * sizeof(struct wf_face);
		struct wf_face *faces = realloc(model->faces, new_size);
		if (!faces) {
			return 0;
		}
		memset(&faces[model->nfaces], 0, sizeof(struct wf_face));
		if (parse_face(line+1, &faces[model->nfaces])) {
			model->faces = faces;
			model->nfaces++;
			return 1;
		}
	}
	return 0;
}

static struct wf_model *read_file(FILE *file)
{
	struct wf_model *model;
	const char *line = NULL;
	size_t line_size = 0;
	
	model = calloc(1, sizeof(struct wf_model));
	if (!model) {
		return NULL;
	}
	while (-1 != getline((char **)&line, &line_size, file)) {
		if (!parse_line(line, model) && errno) {
			perror("");
			wf_free(model);
			return NULL;
		}
	}
	
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
		if (model->faces) {
			for (int i = 0; i < model->nfaces; i++) {
				free(model->faces[i].indices);
			}
			free(model->faces);
		}
	}
	free(model);
}
