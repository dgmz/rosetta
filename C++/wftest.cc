#include <iostream>
#include <cassert>
//#include <math.h>

#include <vector>
#include "lib/wavefront.h"

#define EPSILON 0.000001
#define fequal(a,b) (fabs(a - b) < EPSILON)

int main(void)
{
	std::string s(" hola");
	wavefront::skip_space(s);
	std::cout << s << std::endl;
	/*
	struct wf_model *model = NULL;
	model = wf_read("african_head.obj");
	assert(model);
	// vertices
	assert(1258 == model->nvertices);
	assert(model->vertices);
	struct wf_vertex *v = &model->vertices[0];
	assert(fequal(-0.000581696, v->x));
	assert(fequal(-0.734665, v->y));
	assert(fequal(-0.623267, v->z));
	assert(fequal(1.0, v->w));
	v = &model->vertices[model->nvertices - 1];
	assert(fequal(-0.171097, v->x));
	assert(fequal(0.299996, v->y));
	assert(fequal(0.415616, v->z));
	assert(fequal(1.0, v->w));
	// faces
	assert(2492 == model->nfaces);
	assert(model->faces);
	struct wf_face *f = &model->faces[0];
	assert(3 == f->nindices);
	assert(f->indices);
	assert(24 == f->indices[0]);
	assert(25 == f->indices[1]);
	assert(26 == f->indices[2]);
	f = &model->faces[model->nfaces - 1];
	assert(3 == f->nindices);
	assert(f->indices);
	assert(1201 == f->indices[0]);
	assert(1202 == f->indices[1]);
	assert(1200 == f->indices[2]);
	*/
	return 0;
}
