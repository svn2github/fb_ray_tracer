#ifndef __HITINFO_HPP
#define __HITINFO_HPP

#include "vector3D.hpp"
#include "point3D.hpp"
#include "ray.hpp"

namespace ray_tracer {
	class world;
	class surface;
	class hitInfo {
	public:
		hitInfo();
	public:
		double hit_t;
		point3D hit_point;
		point3D hit_relative_point; 
		vector3D normal;
		world *world_ptr;
		surface *surface_ptr;
		ray emission_ray;
		point3D light_position;
	};
}

#endif