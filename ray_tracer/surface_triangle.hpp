#ifndef __SURFACE_TRIANGLE_HPP
#define __SURFACE_TRIANGLE_HPP

#include "surface.hpp"
#include "point3D.hpp"
#include "vector3D.hpp"

namespace ray_tracer {
	class surface_triangle : public surface {
	public:
		surface_triangle();
		surface_triangle(const point3D &, const point3D &, const point3D &);
		bool hit(const ray &, double, hitInfo *) const;
		vector3D get_normal(const point3D &) const;
	private:
		point3D v0, v1, v2;
		vector3D normal;
	};
}

#endif
