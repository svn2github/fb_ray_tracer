
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
		normal = vector3D();
		world_ptr = NULL;
		surface_ptr = NULL;
		ray_ptr = NULL;
	}
}