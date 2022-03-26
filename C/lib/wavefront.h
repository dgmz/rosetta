#ifndef WAVEFRONT_H_
#define WAVEFRONT_H_

struct wf_vertex {
	float x;
	float y;
	float z;
	float w;
};

struct wf_face {
	int *indices;
	size_t nindices;
};

struct wf_model {
	struct wf_vertex *vertices;
	size_t nvertices;
	struct wf_face *faces;
	size_t nfaces;
};

struct wf_model *wf_read(const char *name);
void wf_free(struct wf_model *model);

#endif // WAVEFRONT_H_
