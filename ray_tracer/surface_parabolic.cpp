
#include "misc.hpp"
#include "ray.hpp"
#include "surface_parabolic.hpp"

namespace ray_tracer {

	surface_parabolic::surface_parabolic() {
		// Ellipsoid
		// quad.xx = 2;
		// quad.yy = 1;
		// quad.zz = 3;
		// quad.c = -100;
		// x2 + y2 + z = c
		quad.xx = 1;
		quad.yy = 1;
		quad.z = 3;
		quad.c = -10;
		// Sphere
		// quad.xx = 1;
		// quad.yy = 1;
		// quad.zz = 1;
		// quad.c = -40;
	}

	double surface_parabolic::hit(const ray &emission_ray) const {
		return quad.find_root(emission_ray.origin, emission_ray.dir);
	}

	vector3D surface_parabolic::get_normal(const point3D &point) const {
		return vector3D(quad.find_limit_x(point), quad.find_limit_y(point), quad.find_limit_z(point)).normalized();
	}
}