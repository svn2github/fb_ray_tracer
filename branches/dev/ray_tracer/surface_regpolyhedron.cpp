
#include <vector>
#include <cmath>
#include <memory>
#include <algorithm>
#include <functional>
#include "surface_regpolyhedron.hpp"
#include "surface_sphere.hpp"
#include "polyvertex.hpp"
#include "polyvertex_tetrahedron.hpp"
#include "polyvertex_cube.hpp"
#include "polyvertex_octahedron.hpp"
#include "polyvertex_dodecahedron.hpp"
#include "polyvertex_icosahedron.hpp"
#include "polyvertex_truncated_icosahedron.hpp"

// Reference: http://caterpillar.onlyfun.net/Gossip/ComputerGraphics/VetexOfPolyhedron.htm

namespace ray_tracer {

	surface_regpolyhedron::surface_regpolyhedron(int f, double r, const point3D &c) {
		std::unique_ptr<polyvertex> vertices_ptr;
		std::vector<point3D> vertices;

		if (f == 4) {
			vertices_ptr = std::unique_ptr<polyvertex>(new polyvertex_tetrahedron);
		} else if (f == 6) {
			vertices_ptr = std::unique_ptr<polyvertex>(new polyvertex_cube);
		} else if (f == 8) {
			vertices_ptr = std::unique_ptr<polyvertex>(new polyvertex_octahedron);
		} else if (f == 12) {
			vertices_ptr = std::unique_ptr<polyvertex>(new polyvertex_dodecahedron);
		} else if (f == 20) {
			vertices_ptr = std::unique_ptr<polyvertex>(new polyvertex_icosahedron);
		} else if (f == 32) {
			vertices_ptr = std::unique_ptr<polyvertex>(new polyvertex_truncated_icosahedron);
		}
		vertices = vertices_ptr->get_vertices();
		std::transform(vertices.begin(), vertices.end(), vertices.begin(), vertices_transformer(r, vector3D(c.x, c.y, c.z)));
		construct(vertices);

		bounding_surface_ptr = std::unique_ptr<const surface>(new surface_sphere(c, r));
	}

}