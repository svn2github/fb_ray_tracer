
#include "misc.hpp"
#include "surface.hpp"
#include <cmath>

namespace ray_tracer {

	surface_sphere::surface_sphere() {
		center = point3D();
		radius = 0;
	}

	surface_sphere::surface_sphere(const point3D &center_, double radius_) {
		center = center_;
		radius = radius_;
	}

	bool surface_sphere::hit(ray *ray_ptr, double tmin, hit_record *hit_ptr) {
		point3D e = ray_ptr->start, c = center;
		vector3D d = ray_ptr->dir;
		double a = d * (e - c), d2 = d.length2();
		vector3D cc = e - c;
		double delta = a * a - d2 * (cc.length2() - radius * radius);
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

	vector3D surface_sphere::get_normal(point3D *point_ptr) {
		return (*point_ptr - center).normalized();
	}

}
