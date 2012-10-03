
#include "misc.hpp"
#include "ray.hpp"
#include "surface_quadratic.hpp"

namespace ray_tracer {

	surface_quadratic::surface_quadratic() {
		// Ellipsoid
		// coef_xx = 2;
		// coef_yy = 1;
		// coef_zz = 3;
		// coef_const = -100;

		// Parabolic: x2 + y2 - z + c = 0
		coef_xx = 1;
		coef_yy = 1;
// 		coef_z = -1;
		coef_const = -10;
		set_range_z(-10, 10);

		// Sphere
		// coef_xx = 1;
		// coef_yy = 1;
		// coef_zz = 1;
		// coef_const = -40;
	}

	double surface_quadratic::hit(const ray &emission_ray, const surface **hit_surface_ptr) const {
		return find_root(emission_ray.origin, emission_ray.dir);
	}

	vector3D surface_quadratic::get_normal_vector(const point3D &point) const {
		return vector3D(gradient_x(point), gradient_y(point), gradient_z(point)).normalized(); 
	}
}
