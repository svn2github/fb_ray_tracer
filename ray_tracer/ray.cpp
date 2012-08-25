
#include "ray.hpp"

namespace ray_tracer {

	ray::ray() {
		start = point3D();
		dir = vector3D();
	}

	ray::ray(const point3D &start_, const vector3D &dir_) { 
		start = start_;
		dir = dir_; 
	}
}