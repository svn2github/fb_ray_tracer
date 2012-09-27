
#include "tracer.hpp"
#include "ray.hpp"
#include "world.hpp"
#include "camera_spherical.hpp"

namespace ray_tracer {
	
	camera_spherical::camera_spherical() {
		fov_u = pi / 4;
		fov_v = pi / 4;
	}

	camera_spherical::camera_spherical(const point3D &eye_, const point3D &lookat_, const vector3D &up_, double fov_u_, double fov_v_) : camera(eye_, lookat_, up_) {
		fov_u = fov_u_;
		fov_v = fov_v_;
	}
	
	colorRGB camera_spherical::render_scene(double x, double y, int w, int h, hitInfo *info_ptr) const {
		double u = (x / w - 0.5) * 2;
		double v = (y / h - 0.5) * 2;
		double alpha = pi - u * fov_u;
		double beta = pi / 2 - v * fov_v;

		return camera::render_scene(eye, axis_w * sin(beta) * cos(alpha) + axis_u * sin(beta) * sin(alpha) + axis_v * cos(beta), info_ptr);
	}
}