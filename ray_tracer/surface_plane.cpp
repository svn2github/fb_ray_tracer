
#include "misc.hpp"
#include "surface.hpp"
#include <cmath>

namespace ray_tracer {

	surface_plane::surface_plane() {
		point_on_plane = point3D();
		normal = vector3D();
	}

	surface_plane::surface_plane(const point3D &point_, const vector3D &normal_) {
		point_on_plane = point_;
		normal = normal_;
	}

	bool surface_plane::hit(ray *ray_ptr, double tmin, point3D *contact_ptr) {
		double deno = normal * ray_ptr->dir;

		if (ray_dblcmp(deno) == 0) {
			return false;
		} else {
			double t = (point_on_plane - ray_ptr->start) * normal / deno;
			if (ray_dblcmp(t - tmin) == -1) {
				return false;
			}
			contact_ptr->x = ray_ptr->start.x + ray_ptr->dir.x * t;
			contact_ptr->y = ray_ptr->start.y + ray_ptr->dir.y * t;
			contact_ptr->z = ray_ptr->start.z + ray_ptr->dir.z * t;
			return true;
		}
	}

	vector3D surface_plane::get_normal(point3D *point_ptr) {
		return normal.normalized();
	}

}
