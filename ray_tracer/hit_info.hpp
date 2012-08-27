#ifndef __HIT_INFO_HPP
#define __HIT_INFO_HPP

#include "vector3D.hpp"
#include "point3D.hpp"

namespace ray_tracer {
	class world;
	class surface;
	class ray;
	class hit_info {
	public:
		hit_info();
	public:
		double hit_t;
		point3D hit_point;
		vector3D normal;
		world *world_ptr;
		surface *surface_ptr;
		ray *ray_ptr;
	};
}

#endif