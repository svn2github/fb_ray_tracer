
#include "misc.hpp"
#include "surface_sphere.hpp"
#include <cmath>

namespace ray_tracer {

	surface_sphere::surface_sphere() {
		set_center(point3D());
		set_radius(0);
	}

	surface_sphere::surface_sphere(const point3D &center_, double radius_) {
		set_center(center_);
		set_radius(radius_);
	}

	bool surface_sphere::hit(ray *ray_ptr, double tmin, hit_record *hit_ptr) const {
		point3D e = ray_ptr->get_origin(), c = center;
		vector3D d = ray_ptr->get_dir();
		double a = d * (e - c), d2 = d.length2();
		vector3D cc = e - c;
		double delta = a * a - d2 * (cc.length2() - radius2);
		double t;

		if (ray_dblcmp(delta) == -1) {
			return false;
		} else {
			t = (-a - sqrt(delta + ray_eps)) / d2;
			if (ray_dblcmp(t - tmin) == -1) {
				return false;
			}
			hit_ptr->hit_t = t;
			return true;
		}
	}

	vector3D surface_sphere::get_normal(point3D *point_ptr) const {
		return (*point_ptr - center).normalized();
	}

}
