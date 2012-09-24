
#include <cmath>
#include "misc.hpp"
#include "ray.hpp"
#include "surface_plane.hpp"

namespace ray_tracer {

	surface_plane::surface_plane() {
		point_on_plane = point3D(0, 0, 0);
		normal = vector3D(0, 0, 1);
	}

	surface_plane::surface_plane(const point3D &point_, const vector3D &normal_) {
		point_on_plane = point_;
		normal = normal_.normalized();
	}

	bool surface_plane::hit(const ray &emission_ray, double tmin, hitInfo *info_ptr) const {
		double deno = normal * emission_ray.get_dir();
		double t = (point_on_plane - emission_ray.get_origin()) * normal / deno;
		
		if (dblcmp(deno) == 0 || t < tmin) {
			return false;
		}
		info_ptr->hit_t = t;
		return true;
	}

	vector3D surface_plane::get_normal(const point3D &point) const {
		return normal;
	}
}