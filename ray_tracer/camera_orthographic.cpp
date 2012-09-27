
#include "tracer.hpp"
#include "ray.hpp"
#include "world.hpp"
#include "camera_orthographic.hpp"

namespace ray_tracer {
	
	camera_orthographic::camera_orthographic() { }

	camera_orthographic::camera_orthographic(const point3D &eye_, const point3D &lookat_, const vector3D &up_, double fov_u_, double fov_v_) : camera(eye_, lookat_, up_) { 
		fov_u = fov_u_;
		fov_v = fov_v_;
	}
	
	colorRGB camera_orthographic::render_scene(double x, double y, int w, int h, hitInfo *info_ptr) const {
		double u = (x / w - 0.5) * fov_u;
		double v = (y / h - 0.5) * fov_v;
		
		return camera::render_scene(eye + u * axis_u + v * axis_v, -axis_w, info_ptr);
	}
}