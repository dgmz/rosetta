#include <stdlib.h>
#include <assert.h>
#include <math.h>

#include "lib/wavefront.h"

#define EPSILON 0.000001
#define fequal(a,b) (fabs(a - b) < EPSILON)

int main(void)
{
	struct wf_model *model = NULL;
	model = wf_read("african_head.obj");
	assert(model);
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
	return 0;
}
