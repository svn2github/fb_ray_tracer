
#include "tracer.hpp"
#include "ray.hpp"
#include "world.hpp"
#include "camera_pinhole.hpp"

namespace ray_tracer {
	
	camera_pinhole::camera_pinhole() {
		fov_u = pi / 4;
		fov_v = pi / 4;
		tan_fov_u_coef = 2 * tan(fov_u);
		tan_fov_v_coef = 2 * tan(fov_v);
	}

	camera_pinhole::camera_pinhole(const point3D &eye_, const point3D &lookat_, const vector3D &up_, double fov_u_, double fov_v_) : camera(eye_, lookat_, up_) {
		fov_u = fov_u_;
		fov_v = fov_v_;
		tan_fov_u_coef = 2 * tan(fov_u);
		tan_fov_v_coef = 2 * tan(fov_v);
	}
	
	colorRGB camera_pinhole::render_scene(double x, double y, int w, int h, hitInfo *info_ptr) const {
		double u = (x / w - 0.5) * tan_fov_u_coef;
		double v = (y / h - 0.5) * tan_fov_v_coef;

		return camera::render_scene(eye, -axis_w + u * axis_u + v * axis_v, info_ptr);
	}
}