
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

	bool surface_sphere::hit(ray *ray_ptr, double *tmin_ptr, point3D *contact_ptr) {
		point3D e = ray_ptr->start, c = center;
		vector3D d = ray_ptr->dir;
		double delta = (d * (e - c)) * (d * (e - c)) - (d * d) * ((e - c) * (e - c) - radius * radius);
		double t;

		if (ray_dblcmp(delta) == -1) {
			return false;
		} else {
			t = (-d * (e - c) - sqrt(delta + ray_eps)) / (d * d);
			if (ray_dblcmp(t - *tmin_ptr) == -1) {
				return false;
			}
			contact_ptr->x = ray_ptr->start.x + ray_ptr->dir.x * t;
			contact_ptr->y = ray_ptr->start.y + ray_ptr->dir.y * t;
			contact_ptr->z = ray_ptr->start.z + ray_ptr->dir.z * t;
			*tmin_ptr = t;
			return true;
		}
	}

	vector3D surface_sphere::get_normal(point3D *point_ptr) {
		return (*point_ptr - center).normalized();
	}

}
