
#include "view_plane.hpp"
#include "tracer.hpp"
#include "ray.hpp"
#include "world.hpp"
#include "camera_orthographic.hpp"

namespace ray_tracer {
	
	camera_orthographic::camera_orthographic() {
		eye = point3D();
		lookat = point3D();
		up = vector3D();
		compute_axis();
	}

	camera_orthographic::camera_orthographic(const point3D &eye_, const point3D &lookat_, const vector3D &up_) {
		eye = eye_;
		lookat = lookat_;
		up = up_;
		compute_axis();
	}
	
	colorRGB camera_orthographic::render_scene(int x, int y, int w, int h, world *world_ptr) const {
		double u = world_ptr->get_view_plane()->compute_u(x + 0.5, w);
		double v = world_ptr->get_view_plane()->compute_v(y + 0.5, h);
		hit_info info;

		if (world_ptr->get_hit(&ray(eye + u * axis_u + v * axis_v, -axis_w), &info)) {
			return world_ptr->get_tracer()->ray_color(world_ptr, &info);
		} else {
			return world_ptr->get_background();
		}
	}
}