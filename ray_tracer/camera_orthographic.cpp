
#include "view_plane.hpp"
#include "tracer.hpp"
#include "ray.hpp"
#include "world.hpp"
#include "camera_orthographic.hpp"

namespace ray_tracer {
	
	camera_orthographic::camera_orthographic() { }

	camera_orthographic::camera_orthographic(const point3D &eye_, const point3D &lookat_, const vector3D &up_) : camera(eye_, lookat_, up_) { }
	
	colorRGB camera_orthographic::render_scene(double x, double y, int w, int h, world *world_ptr) const {
		double u = world_ptr->get_view_plane()->compute_u(x + 0.5, w);
		double v = world_ptr->get_view_plane()->compute_v(y + 0.5, h);
		hitInfo info;

		if (world_ptr->get_hit(&ray(eye + u * axis_u + v * axis_v, -axis_w), &info)) {
			return world_ptr->get_tracer()->ray_color(&info);
		} else {
			return world_ptr->get_background();
		}
	}
}