
#include <cmath>
#include "misc.hpp"
#include "ray.hpp"
#include "surface_plane.hpp"

namespace ray_tracer {

	surface_plane::surface_plane() {
		set_point_on_plane(point3D());
		set_normal(vector3D());
	}

	surface_plane::surface_plane(const point3D &point_, const vector3D &normal_) {
		set_point_on_plane(point_);
		set_normal(normal_);
	}

	bool surface_plane::hit(ray *ray_ptr, double tmin, hit_info *hit_ptr) const {
		double deno = normal * ray_ptr->get_dir();
		double t = (point_on_plane - ray_ptr->get_origin()) * normal / deno;
		
		if (t < tmin) {
			return false;
		}
		hit_ptr->hit_t = t;
		return true;
	}

	vector3D surface_plane::get_normal(const point3D &point) const {
		return normal;
	}

}
