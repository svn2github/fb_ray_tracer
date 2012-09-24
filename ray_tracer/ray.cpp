
#include "ray.hpp"

namespace ray_tracer {

	ray::ray() {
		set_origin(point3D(0, 0, 0));
		set_dir(vector3D(0, 0, 1));
	}

	ray::ray(const point3D &origin_, const vector3D &dir_) { 
		set_origin(origin_);
		set_dir(dir_);
	}
}