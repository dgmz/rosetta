#ifndef WAVEFRONT_H_
#define WAVEFRONT_H_

namespace wavefront {

	struct vertex {
		float x;
		float y;
		float z;
		float w;
	};
	
	class face {
		std::vector<int> indices;
	};
	
	class model {
		public:
		std::vector<struct vertex> vertices;
		std::vector<class face> faces;
		
		static model read(const char *name);
	};
	
	void skip_space(std::string &s);
	
}

#endif // WAVEFRONT_H_
