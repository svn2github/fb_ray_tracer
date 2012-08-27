
#include "hit_info.hpp"
#include "vector3D.hpp"
#include "point3D.hpp"
#include "surface.hpp"
#include "ray.hpp"
#include "misc.hpp"

namespace ray_tracer {

	hit_info::hit_info() { 
		hit_t = huge_double;
		hit_point = point3D();
		normal = vector3D();
		world_ptr = NULL;
		surface_ptr = NULL;
		ray_ptr = NULL;
	}
}