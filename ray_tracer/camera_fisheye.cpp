
#include "view_plane.hpp"
#include "tracer.hpp"
#include "ray.hpp"
#include "world.hpp"
#include "point2D.hpp"
#include "camera_fisheye.hpp"

namespace ray_tracer {
	
	camera_fisheye::camera_fisheye() {
		fov = 0;
	}

	camera_fisheye::camera_fisheye(const point3D &eye_, const point3D &lookat_, const vector3D &up_, double fov_) : camera(eye_, lookat_, up_) {
		fov = fov_;
	}
	
	colorRGB camera_fisheye::render_scene(double x, double y, int w, int h, world *world_ptr) {
		point2D pp = point2D((x / w - 0.5) * 2, (y / h - 0.5) * 2);

		if (pp.length_squared() <= 1) {
			double inv_r = pp.inv_length();
			double r = pp.length();
			double sin_alpha = pp.y * inv_r, cos_alpha = pp.x * inv_r;
			double sin_beta = sin(r * fov), cos_beta = cos(r * fov);

			return camera::render_scene(eye, sin_beta * cos_alpha * axis_u + sin_beta * sin_alpha * axis_v - cos_beta * axis_w, world_ptr);
		} else {
			return color_black;
		}
	}
}