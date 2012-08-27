
#include "misc.hpp"
#include "surface_plane.hpp"
#include <cmath>

namespace ray_tracer {

	surface_plane::surface_plane() {
		set_point_on_plane(point3D());
		set_normal(vector3D());
	}

	surface_plane::surface_plane(const point3D &point_, const vector3D &normal_) {
		set_point_on_plane(point_);
		set_normal(normal_);
	}

	bool surface_plane::hit(ray *ray_ptr, double tmin, hit_record *hit_ptr) const {
		double deno = normal * ray_ptr->get_dir();

		if (dblcmp(deno) == 0) {
			return false;
		} else {
			double t = (point_on_plane - ray_ptr->get_origin()) * normal / deno;
			if (dblcmp(t - tmin) == -1) {
				return false;
			}
			hit_ptr->hit_t = t;
			return true;
		}
	}

	vector3D surface_plane::get_normal(point3D *point_ptr) const {
		return normal;
	}

}
