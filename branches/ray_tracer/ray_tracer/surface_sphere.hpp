#ifndef __SURFACE_SPHERE_HPP__
#define __SURFACE_SPHERE_HPP__

#include "surface.hpp"

namespace ray_tracer {
	class surface_sphere : public surface {
	public:
		surface_sphere();
		surface_sphere(const point3D &, double);
		double hit(const ray &, const surface **) const;
		vector3D get_normal_vector(const point3D &) const;
		point3D get_local_point(const point3D &) const;
	private:
		point3D center;
		double radius, radius_squared;
	};
}

#endif
