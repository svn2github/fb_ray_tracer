
#include "hitInfo.hpp"
#include "vector3D.hpp"
#include "point3D.hpp"
#include "surface.hpp"
#include "ray.hpp"
#include "misc.hpp"

namespace ray_tracer {

	hitInfo::hitInfo() { 
		hit_t = huge_double;
		hit_point = point3D();
		hit_relative_point = point3D();
		normal = vector3D();
		world_ptr = NULL;
		surface_ptr = NULL;
		emission_ray = ray();
		light_position = point3D();
	}
}