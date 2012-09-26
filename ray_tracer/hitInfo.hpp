#ifndef __HITINFO_HPP__
#define __HITINFO_HPP__

#include "vector3D.hpp"
#include "point3D.hpp"
#include "ray.hpp"

namespace ray_tracer {

	class world;
	class view_plane;
	class surface;
	class camera;
	class light;
	class sampler_iterator;

	class hitInfo {
	public:
		hitInfo();
	public:
		double hit_time;
		point3D hit_point;
		point3D hit_relative_point; 
		vector3D normal;
		const world *world_ptr;
		const view_plane *view_plane_ptr;
		const surface *surface_ptr;
		const camera *camera_ptr;
		const light *light_ptr;
		sampler_iterator *sampler_iterator_ptr;
		ray emission_ray;
		int ray_tracing_depth;
	};
}

#endif