#ifndef __SURFACE_SPHERE_HPP__
#define __SURFACE_SPHERE_HPP__

#include "surface.hpp"

namespace ray_tracer {
	class surface_sphere : public surface {
	public:
		surface_sphere();
		surface_sphere(const point3D &, double);
		bool two_face() const;
		double hit(const ray &) const;
		vector3D get_normal(const point3D &) const;
		point3D get_relative_pos(const point3D &) const;
	private:
		point3D center;
		double radius, radius_squared;
	};
}

#endif
