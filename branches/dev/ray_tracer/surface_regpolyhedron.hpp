#ifndef __SURFACE_REGPOLYHEDRON_HPP__
#define __SURFACE_REGPOLYHEDRON_HPP__

#include <vector>
#include "surface.hpp"
#include "surface_convexhull.hpp"
#include "vector3D.hpp"
#include "point3D.hpp"

namespace ray_tracer {
	
	class vertices_transformer {
	private:
		double r;
		vector3D v;
	public:
		vertices_transformer(double r_, const vector3D &v_) : r(r_), v(v_) { }
		point3D operator() (const point3D &p) {
			return p.normalized() * r + v;
		}
	};

	class surface_regpolyhedron : public surface_convexhull {
	public:
		surface_regpolyhedron(double, const point3D &, int, int = 0);
	};
}

#endif
