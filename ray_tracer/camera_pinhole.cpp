
#include "view_plane.hpp"
#include "tracer.hpp"
#include "ray.hpp"
#include "world.hpp"
#include "camera_pinhole.hpp"

namespace ray_tracer {
	
	camera_pinhole::camera_pinhole() {
		view_dist = 0;
	}

	camera_pinhole::camera_pinhole(const point3D &eye_, const point3D &lookat_, const vector3D &up_, double view_dist_) : camera(eye_, lookat_, up_) {
		view_dist = view_dist_;
	}

	void camera_pinhole::zoom(double factor) {
		view_dist *= factor;
	}
	
	colorRGB camera_pinhole::render_scene(double x, double y, int w, int h, world *world_ptr) const {
		double u = world_ptr->get_view_plane()->compute_u(x, w);
		double v = world_ptr->get_view_plane()->compute_v(y, h);
		hitInfo info;

		if (world_ptr->get_hit(ray(eye, (-axis_w * view_dist + u * axis_u + v * axis_v).normalized()), &info)) {
			return world_ptr->get_tracer()->ray_color(&info);
		} else {
			return world_ptr->get_background();
		}
	}
}