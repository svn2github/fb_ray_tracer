
#include "polyvertex.hpp"
#include "convexhull.hpp"

namespace ray_tracer {

	polyvertex::~polyvertex() { }

	const std::vector<point3D> &polyvertex::get_vertices() const {
		return vertices;
	}
	
	void polyvertex::reflect() {
		int sz = vertices.size();

		for (int i = 0; i < sz; ++i) {
			vertices.push_back(-vertices[i]);
		}
	}

	void polyvertex::subdivide(int depth) {
		std::vector<edge_t> edges;

		do {
			edges = convexhull(vertices).construct_hull().second;
			for (std::vector<edge_t>::const_iterator it = edges.begin(); it != edges.end(); ++it) {
				vertices.push_back((vertices[std::get<0>(*it)] + vertices[std::get<1>(*it)]).normalized());
			}
		} while (--depth != 0);
	}
}
