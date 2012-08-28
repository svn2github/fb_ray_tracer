
#include "view_plane.hpp"
#include "tracer.hpp"
#include "ray.hpp"
#include "world.hpp"
#include "camera_thinlens.hpp"
#include "sampler_random.hpp"

namespace ray_tracer {

	const int num_samplers = 100;

	void camera_thinlens::init_sampler(int num) {
		smpler = new sampler_random();
		smpler->generate(num);
		smpler->map_sample_to_disk();
	}

	camera_thinlens::camera_thinlens() {
		eye = point3D();
		lookat = point3D();
		up = vector3D();
		compute_axis();
		view_dist = 0;
		focal_dist = 0;
		lens_radius = 0;
		init_sampler(num_samplers);
	}

	camera_thinlens::camera_thinlens(const point3D &eye_, const point3D &lookat_, const vector3D &up_, double view_dist_, double focal_dist_, double lens_radius_) {
		eye = eye_;
		lookat = lookat_;
		up = up_;
		compute_axis();
		view_dist = view_dist_;
		focal_dist = focal_dist_;
		lens_radius = lens_radius_;
		init_sampler(num_samplers);
	}

	camera_thinlens::~camera_thinlens() {
		delete smpler;
	}

	colorRGB camera_thinlens::render_scene(int x, int y, int w, int h, world *world_ptr) const {
		double u = world_ptr->get_view_plane()->compute_u(x + 0.5, w);
		double v = world_ptr->get_view_plane()->compute_v(y + 0.5, h);
		hit_info info;
		point3D focal_point, origin, origin_fixed;
		colorRGB color = color_black;
		point2D sample_point;

		focal_point = eye + (-axis_w * view_dist + u * axis_u + v * axis_v) * (focal_dist / view_dist);
		origin = eye - 0.5 * axis_u - 0.5 * axis_v;
		for (int i = 1; i <= num_samplers; i += 1) {
			sample_point = smpler->get_sampler_zoomed(lens_radius);
			origin_fixed = origin + sample_point.x * axis_u + sample_point.y * axis_v;
			if (world_ptr->get_hit(&ray(origin_fixed, (focal_point - origin_fixed).normalized()), &info)) {
				color += world_ptr->get_tracer()->ray_color(world_ptr, &info);
			} else {
				color += world_ptr->get_background();
			}
		}
		return color / num_samplers;
	}
}
