
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
	
	ray camera_orthographic::get_ray(int x, int y, int w, int h, view_plane *plane_ptr) const {
		double u = plane_ptr->get_left() + (plane_ptr->get_right() - plane_ptr->get_left()) * ((double)x + 0.5) / (double)w;
		double v = plane_ptr->get_bottom() + (plane_ptr->get_top() - plane_ptr->get_bottom()) * ((double)y + 0.5) / (double)h;
		point3D origin;
		vector3D dir;

		dir = -axis_w;
		origin = eye + u * axis_u + v * axis_v;
		return ray(origin, dir);
	}
}