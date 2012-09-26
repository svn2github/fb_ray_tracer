
#include "view_plane.hpp"
#include "tracer.hpp"
#include "ray.hpp"
#include "world.hpp"
#include "camera_thinlens.hpp"

namespace ray_tracer {

	camera_thinlens::camera_thinlens() {
		view_dist = 0;
		focal_dist = 0;
		lens_radius = 0;
	}

	camera_thinlens::camera_thinlens(const point3D &eye_, const point3D &lookat_, const vector3D &up_, double view_dist_, double focal_dist_, double lens_radius_) : camera(eye_, lookat_, up_) {
		view_dist = view_dist_;
		focal_dist = focal_dist_;
		lens_radius = lens_radius_;
	}

	void camera_thinlens::zoom(double factor) {
		view_dist *= factor;
	}

	colorRGB camera_thinlens::render_scene(double x, double y, int w, int h, hitInfo *info_ptr) const {
		const view_plane *plane_ptr = info_ptr->view_plane_ptr;
		double u = plane_ptr->compute_u(x, w);
		double v = plane_ptr->compute_v(y, h);
		hitInfo info;
		point3D focal_point, origin, origin_fixed;
		point2D sample_point;

		focal_point = eye + (-axis_w * view_dist + u * axis_u + v * axis_v) * (focal_dist / view_dist);
		origin = eye - 0.5 * axis_u - 0.5 * axis_v;
		sample_point = info_ptr->sampler_iterator_ptr->get_sampler_disk_zoomed(sampler_set_camera_thinlens, lens_radius);
		origin_fixed = origin + sample_point.x * axis_u + sample_point.y * axis_v;
		return camera::render_scene(origin_fixed, (focal_point - origin_fixed).normalized(), info_ptr);
	}
}
