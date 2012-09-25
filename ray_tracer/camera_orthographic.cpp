
#include "view_plane.hpp"
#include "tracer.hpp"
#include "ray.hpp"
#include "world.hpp"
#include "camera_orthographic.hpp"

namespace ray_tracer {
	
	camera_orthographic::camera_orthographic() { }

	camera_orthographic::camera_orthographic(const point3D &eye_, const point3D &lookat_, const vector3D &up_) : camera(eye_, lookat_, up_) { }
	
	colorRGB camera_orthographic::render_scene(double x, double y, int w, int h, hitInfo *info_ptr) {
		world *world_ptr = info_ptr->world_ptr;
		double u = world_ptr->get_view_plane()->compute_u(x, w);
		double v = world_ptr->get_view_plane()->compute_v(y, h);
		
		return camera::render_scene(eye + u * axis_u + v * axis_v, -axis_w, info_ptr);
	}
}