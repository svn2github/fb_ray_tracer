
#include "hitInfo.hpp"
#include "vector3D.hpp"
#include "point3D.hpp"
#include "surface.hpp"
#include "ray.hpp"
#include "misc.hpp"

namespace ray_tracer {

	hitInfo::hitInfo() { 
		hit_t = huge_double;
		hit_point = point3D(0, 0, 0);
		hit_relative_point = point3D(0, 0, 0);
		normal = vector3D(0, 0, 0);
		world_ptr = NULL;
		surface_ptr = NULL;
		emission_ray = ray();
		ray_tracing_depth = 5;
		light_position = point3D(0, 0, 0);
	}
}