#include <vector>
#include <fstream>
#include <string>
#include <cassert>

#include "wavefront.h"

namespace wavefront {

//static 
void skip_space(std::string &s)
{
	size_t pos;
	
	pos = s.find_first_not_of(" \t");
	if (std::string::npos != pos) {
		s.erase(0, pos);
	}
}

/*
static double read_double(const char **s)
{
	char next = **s;
	if ('\r' != next && '\n' != next && '\0' != next) {
		double d = strtod(*s, (char **)s);
		if (ERANGE != errno) {
			next = **s;
			if (' ' == next || '\t' == next || '\0' == next 
			|| '\r' == next || '\n' == next) {
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
			indices = realloc(face->indices, (face->nindices + 1) 
				* sizeof(int));
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
	if ('\r' == *line || '\n' == *line || '\0' == *line 
	|| 2 < face->nindices) {
		return 1;
	}
	return 0;
}

static void parse_line(std::string &line, model &model)
{	
	skip_space(line);
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
*/

static void parse_line(std::string &line, model &m)
{	
}

model model::read(const char *name)
{
	std::string line;
	model m;
	
	assert(name);
	std::ifstream file(name);
	while (std::getline(file, line)) {
		parse_line(line, m);
	}
	file.close();
	
	return m;
}

}
