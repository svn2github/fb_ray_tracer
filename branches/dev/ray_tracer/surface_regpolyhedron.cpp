
#include "surface_regpolyhedron.hpp"
#include <vector>
#include <cmath>

// Reference: http://caterpillar.onlyfun.net/Gossip/ComputerGraphics/VetexOfPolyhedron.htm

namespace ray_tracer {

	surface_regpolyhedron::surface_regpolyhedron(int f, double r, const point3D &c) {
		const double s2 = sqrt(2), s3 = sqrt(3), s5 = sqrt(5), t1 = (s5 + 1) / 2, t2 = (s5 - 1) / 2, k1 = sqrt(t1 / s5), k2 = sqrt(t2 / s5); 
		std::vector<point3D> vertices;
		vector3D vc = vector3D(c.x, c.y, c.z);
		if (f == 4) {
			vertices.push_back(point3D(0, r, 0));
			vertices.push_back(point3D(0, -r / 3, r * 2 * s2 / 3));
			vertices.push_back(point3D(r * s2 / s3, -r / 3, -r * s2/ 3));
			vertices.push_back(point3D(-r * s2 / s3, -r / 3, -r * s2 / 3));
		} else if (f == 6) {
			vertices.push_back(point3D(0, r, 0));
			vertices.push_back(point3D(0, r / 3, r * 2 * s2 / 3));
			vertices.push_back(point3D(r * s2 / s3, r / 3, -r * s2 / 3));
			vertices.push_back(point3D(-r * s2 / s3, r / 3, - r * s2 / 3));
			reflect(vertices);
		} else if (f == 8) {
			vertices.push_back(point3D(0, r, 0));
			vertices.push_back(point3D(0, 0, r));
			vertices.push_back(point3D(r, 0, 0));
			reflect(vertices);
		} else if (f == 12) {
			vertices.push_back(point3D(0, r, 0));
			vertices.push_back(point3D(0, r * s5 / 3, r * 2 / 3));
			vertices.push_back(point3D(r * s3 / 3, r * s5 / 3, -r / 3));
			vertices.push_back(point3D(-r * s3 / 3, r * s5 / 3, -r / 3));
			vertices.push_back(point3D(r * s3 / 3, r / 3, r * s5 / 3));
			vertices.push_back(point3D(r * t1 * s3 / 3, r / 3, r * t2 * t2 / 3));
			vertices.push_back(point3D(r * t2 * s3 / 3, r / 3, -r * t1 * t1 / 3));
			vertices.push_back(point3D(-r * t2 * s3 / 3, r / 3, -r * t1 * t1 / 3));
			vertices.push_back(point3D(-r * t1 * s3 / 3, r / 3, r * t2 * t2 / 3));
			vertices.push_back(point3D(-r * s3 / 3, r / 3, r * s5 / 3));
			reflect(vertices);
		} else if (f == 20) {
			vertices.push_back(point3D(0, r, 0));
			vertices.push_back(point3D(0, r / s5, r * 2 / s5));
			vertices.push_back(point3D(r * k1, r / s5, r * t2 / s5));
			vertices.push_back(point3D(r * k2, r / s5, -r * t1 / s5));
			vertices.push_back(point3D(-r * k2, r / s5, -r * t1 / s5));
			vertices.push_back(point3D(-r * k1, r / s5, r * t2 / s5));
			reflect(vertices);
		}
		for (unsigned int i = 0; i < vertices.size(); ++i) {
			vertices[i] += vc;
		}
		construct(vertices);
	}

	void surface_regpolyhedron::reflect(std::vector<point3D> &vertices) {
		int sz = vertices.size();

		for (int i = 0; i < sz; ++i) {
			vertices.push_back(-vertices[i]);
		}
	}
}