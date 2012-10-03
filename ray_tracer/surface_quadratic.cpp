
#include "misc.hpp"
#include "ray.hpp"
#include "surface_quadratic.hpp"

namespace ray_tracer {

	surface_quadratic::surface_quadratic() {
		// Ellipsoid
		// xx = 2;
		// yy = 1;
		// zz = 3;
		// c = -100;

		// Parabolic: x2 + y2 - z + c = 0
		xx = 1;
		yy = 1;
// 		z = -1;
		c = -10;
		set_range_z(-10, 10);

		// Sphere
		// xx = 1;
		// yy = 1;
		// zz = 1;
		// c = -40;
	}

	double surface_quadratic::hit(const ray &emission_ray, const surface **hit_surface_ptr) const {
		return find_root(emission_ray.origin, emission_ray.dir);
	}

	vector3D surface_quadratic::get_normal_vector(const point3D &point) const {
		return vector3D(gradient_x(point), gradient_y(point), gradient_z(point)).normalized(); 
	}
}
