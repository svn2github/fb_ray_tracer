#ifndef __SURFACE_REGPOLYHEDRON_HPP__
#define __SURFACE_REGPOLYHEDRON_HPP__

#include "surface.hpp"
#include "surface_convexhull.hpp"
#include <vector>

namespace ray_tracer {
	class surface_regpolyhedron : public surface_convexhull {
	public:
		surface_regpolyhedron(int, double, const point3D &);
	private:
		void reflect(std::vector<point3D> &);
		void subdivide(double, int, std::vector<point3D> &);
	};
}

#endif
