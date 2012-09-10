
#include "view_plane.hpp"
#include "tracer.hpp"
#include "ray.hpp"
#include "world.hpp"
#include "camera_pinhole.hpp"

namespace ray_tracer {
	
	camera_pinhole::camera_pinhole() {
		eye = point3D();
		lookat = point3D();
		up = vector3D();
		compute_axis();
		view_dist = 0;
	}

	camera_pinhole::camera_pinhole(const point3D &eye_, const point3D &lookat_, const vector3D &up_, double view_dist_) {
		eye = eye_;
		lookat = lookat_;
		up = up_;
		compute_axis();
		view_dist = view_dist_;
	}

	void camera_pinhole::zoom(double factor) {
		view_dist *= factor;
	}
	
	colorRGB camera_pinhole::render_scene(double x, double y, int w, int h, world *world_ptr) const {
		double u = world_ptr->get_view_plane()->compute_u(x + 0.5, w);
		double v = world_ptr->get_view_plane()->compute_v(y + 0.5, h);
		hit_info info;

		if (world_ptr->get_hit(&ray(eye, (-axis_w * view_dist + u * axis_u + v * axis_v).normalized()), &info)) {
			return world_ptr->get_tracer()->ray_color(&info);
		} else {
			return world_ptr->get_background();
		}
	}
}