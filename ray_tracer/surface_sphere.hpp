#ifndef __SURFACE_SPHERE_HPP
#define __SURFACE_SPHERE_HPP

#include "surface.hpp"

namespace ray_tracer {
	class surface_sphere : public surface {
	public:
		surface_sphere();
		surface_sphere(const point3D &, double);
		bool hit(const ray &, double, hitInfo *) const;
		vector3D get_normal(const point3D &) const;
		point3D get_relative_pos(const point3D &) const;
	private:
		point3D center;
		double radius, radius_squared;
	};
}

#endif
