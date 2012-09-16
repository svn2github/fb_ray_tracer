
#include "ray.hpp"
#include "light.hpp"
#include "surface.hpp"
#include "view_plane.hpp"
#include "tracer.hpp"
#include "camera.hpp"
#include "world.hpp"
#include "filter_gaussian_blur.hpp"

namespace ray_tracer {

	world::world(bool antialiasing_) {
		tracer_ptr = new tracer;
		fog_ptr = NULL;
		filter_ptr = NULL;
		set_ambient(color_black);
		antialiasing_enabled = false;
		if (antialiasing_) {
			enable_antialiasing();
		}
	}

	world::~world() {
		delete tracer_ptr;
		if (antialiasing_enabled) {
			disable_antialiasing();
		}
	}

	bool world::get_hit(ray *ray_ptr, hitInfo *info_ptr) {
		bool hit_flag = false;
		static hitInfo temp;
		surface *surface_ptr;

		info_ptr->hit_t = huge_double;
		hit_flag = false;
		for (std::vector<surface *>::iterator iter = surfaces.begin(); iter != surfaces.end(); ++iter) {
			surface_ptr = (*iter);
			if (surface_ptr->hit(ray_ptr, 0, &temp)) {
				if (temp.hit_t < info_ptr->hit_t) {
					info_ptr->hit_t = temp.hit_t;
					info_ptr->surface_ptr = surface_ptr;
					hit_flag = true;
				}
			}
		}
		if (hit_flag) { 
			info_ptr->hit_point = ray_ptr->get_origin() + ray_ptr->get_dir() * info_ptr->hit_t;
			info_ptr->hit_relative_point = info_ptr->surface_ptr->get_relative_pos(info_ptr->hit_point);
			info_ptr->normal = info_ptr->surface_ptr->get_normal(info_ptr->hit_point);
			info_ptr->world_ptr = this;
			info_ptr->ray_ptr = ray_ptr;
		}
		return hit_flag;
	}

	void world::render_scene() {
		int *buffer_ptr = pixal_buffer_ptr;
		colorRGB color;
		point2D sample_point;

		for (int y = 0; y < dest_h; y += 1) {
			for (int x = 0; x < dest_w; x += 1) {
				color = color_black;
				if (antialiasing_enabled) {
					for (int i = 1; i <= num_antialiasing_sampler; i += 1) {
						sample_point = sampler_ptr->get_sampler_unit();
						color += camera_ptr->render_scene(x + sample_point.x, y + sample_point.y, dest_w, dest_h, this);
					}
					color = color / num_antialiasing_sampler;
				} else {
					color = camera_ptr->render_scene(x, y, dest_w, dest_h, this);
				}
				*buffer_ptr ++ = color.clamp_to_int();
			}
		}
		if (filter_ptr != NULL) {
			filter_ptr->apply_filter(pixal_buffer_ptr, dest_w, dest_h);
		}
	}
}