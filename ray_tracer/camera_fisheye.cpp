
#include "view_plane.hpp"
#include "tracer.hpp"
#include "ray.hpp"
#include "world.hpp"
#include "point2D.hpp"
#include "camera_fisheye.hpp"

namespace ray_tracer {
	
	camera_fisheye::camera_fisheye() {
		eye = point3D();
		lookat = point3D();
		up = vector3D();
		compute_axis();
		view_dist = 0;
		fov = 0;
	}

	camera_fisheye::camera_fisheye(const point3D &eye_, const point3D &lookat_, const vector3D &up_, double fov_) {
		eye = eye_;
		lookat = lookat_;
		up = up_;
		compute_axis();
		view_dist = 0;
		fov = fov_;
	}
	
	colorRGB camera_fisheye::render_scene(int x, int y, int w, int h, world *world_ptr) const {
		point2D pp = point2D(((x + 0.5) / w - 0.5) * 2, ((y + 0.5) / h - 0.5) * 2);

		if (pp.length2() <= 1) {
			double inv_r = pp.inv_length();
			double r = pp.length();
			double sin_alpha = pp.y * inv_r, cos_alpha = pp.x * inv_r;
			double sin_beta = sin(r * fov), cos_beta = cos(r * fov);
			hit_info info;

			if (world_ptr->get_hit(&ray(eye, sin_beta * cos_alpha * axis_u + sin_beta * sin_alpha * axis_v - cos_beta * axis_w), &info)) {
				return world_ptr->get_tracer()->ray_color(world_ptr, &info);
			} else {
				return world_ptr->get_background();
			}
		} else {
			return world_ptr->get_background();
		}
	}
}