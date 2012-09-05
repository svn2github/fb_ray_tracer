
#include <cmath>
#include "misc.hpp"
#include "ray.hpp"
#include "surface_disk.hpp"

namespace ray_tracer {

	surface_disk::surface_disk() {
		set_center(point3D());
		set_normal(vector3D());
		set_radius(0);
	}

	surface_disk::surface_disk(const point3D &center_, const vector3D &normal_, double radius) {
		set_center(center_);
		set_normal(normal_);
		set_radius(radius);
	}

	bool surface_disk::hit(ray *ray_ptr, double tmin, hit_info *hit_ptr) const {
		double deno = normal * ray_ptr->get_dir();
		double t = (center - ray_ptr->get_origin()) * normal / deno;
		point3D p;

		if (dblcmp(deno) == 0 || t < tmin) {
			return false;
		}
		p = ray_ptr->get_origin() + ray_ptr->get_dir() * t;
		if ((center - p).length_squared() > radius_squared) {
			return false;
		}
		hit_ptr->hit_t = t;
		return true;
	}

	vector3D surface_disk::get_normal(const point3D &point) const {
		return normal;
	}
}
