
#include <cmath>
#include "misc.hpp"
#include "ray.hpp"
#include "surface_sphere.hpp"

namespace ray_tracer {

	surface_sphere::surface_sphere() {
		set_center(point3D());
		set_radius(0);
	}

	surface_sphere::surface_sphere(const point3D &center_, double radius_) {
		set_center(center_);
		set_radius(radius_);
	}

	bool surface_sphere::hit(const ray &emission_ray, double tmin, hitInfo *info_ptr) const {
		point3D o = emission_ray.get_origin(), c = center;
		vector3D d = emission_ray.get_dir();
		double a = d * (o - c), d2 = d.length_squared();
		vector3D cc = o - c;
		double cc2 = cc.length_squared();
		double delta = a * a - d2 * (cc2 - radius_squared);
		double t;

		if (delta < 0) {
			return false;
		} else {
			if (cc2 < radius_squared) {
				t = (-a + sqrt(delta)) / d2;
			} else {
				t = (-a - sqrt(delta)) / d2;
			}
			if (t < tmin) {
				return false;
			}
			info_ptr->hit_t = t;
			return true;
		}
	}

	vector3D surface_sphere::get_normal(const point3D &point) const {
		return (point - center).normalized();
	}

	point3D surface_sphere::get_relative_pos(const point3D &point) const {
		return (point - center).to_point();
	}
}
