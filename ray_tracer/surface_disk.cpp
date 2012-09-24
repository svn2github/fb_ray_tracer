
#include <cmath>
#include "misc.hpp"
#include "ray.hpp"
#include "surface_disk.hpp"

namespace ray_tracer {

	surface_disk::surface_disk() {
		center = point3D(0, 0, 0);
		normal = vector3D(0, 0, 1);
		radius = 1;
		radius_squared = 1;
	}

	surface_disk::surface_disk(const point3D &center_, const vector3D &normal_, double radius_) {
		center = center_;
		normal = normal_.normalized();
		radius = radius_;
		radius_squared = radius_ * radius_;
	}

	bool surface_disk::hit(const ray &emission_ray, double tmin, hitInfo *info_ptr) const {
		double deno = normal * emission_ray.get_dir();
		double t = (center - emission_ray.get_origin()) * normal / deno;
		point3D p;

		if (dblcmp(deno) == 0 || t < tmin) {
			return false;
		}
		p = emission_ray.get_origin() + emission_ray.get_dir() * t;
		if ((center - p).length_squared() > radius_squared) {
			return false;
		}
		info_ptr->hit_t = t;
		return true;
	}

	vector3D surface_disk::get_normal(const point3D &point) const {
		return normal;
	}
}
