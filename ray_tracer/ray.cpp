
#include "ray.hpp"

namespace ray_tracer {

	ray::ray() {
		origin = point3D(0, 0, 0);
		dir = vector3D(0, 0, 1);
	}

	ray::ray(const point3D &origin_, const vector3D &dir_) { 
		origin = origin_;
		dir = dir_;
	}
}