
#include "tracer.hpp"
#include "ray.hpp"
#include "world.hpp"
#include "camera_thinlens.hpp"

namespace ray_tracer {

	camera_thinlens::camera_thinlens() {
		fov_u = pi / 4;
		fov_v = pi / 4;
		focal_dist = 100;
		lens_radius = 1;
		tan_fov_u_coef = 2 * tan(fov_u);
		tan_fov_v_coef = 2 * tan(fov_v);
	}

	camera_thinlens::camera_thinlens(const point3D &eye_, const point3D &lookat_, const vector3D &up_, double fov_u_, double fov_v_, double focal_dist_, double lens_radius_) : camera(eye_, lookat_, up_) {
		fov_u = fov_u_;
		fov_v = fov_v_;
		focal_dist = focal_dist_;
		lens_radius = lens_radius_;
		tan_fov_u_coef = 2 * tan(fov_u);
		tan_fov_v_coef = 2 * tan(fov_v);
	}

	colorRGB camera_thinlens::render_scene(double x, double y, int w, int h, hitInfo *info_ptr) const {
		double u = (x / w - 0.5) * tan_fov_u_coef;
		double v = (y / h - 0.5) * tan_fov_v_coef;
		hitInfo info;
		point3D focal_point, origin, origin_fixed;
		point2D sample_point;

		focal_point = eye + (-axis_w + u * axis_u + v * axis_v) * focal_dist;
		origin = eye - 0.5 * axis_u - 0.5 * axis_v;
		sample_point = info_ptr->sampler_iterator_ptr->get_sampler_disk_zoomed(sampler_set_camera_thinlens, lens_radius);
		origin_fixed = origin + sample_point.x * axis_u + sample_point.y * axis_v;
		return camera::render_scene(origin_fixed, (focal_point - origin_fixed).normalized(), info_ptr);
	}
}
