
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
		// Parabolic: x2 + y2 + z = c
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
		return vector3D(quad.gradient_x(point), quad.gradient_y(point), quad.gradient_z(point)).normalized(); 
	}
}