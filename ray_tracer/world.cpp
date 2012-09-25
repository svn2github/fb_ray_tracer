
#include "ray.hpp"
#include "light.hpp"
#include "surface.hpp"
#include "view_plane.hpp"
#include "tracer.hpp"
#include "camera.hpp"
#include "sampler_single.hpp"
#include "world.hpp"

namespace ray_tracer {

	world::world() {
		tracer_ptr = new tracer;
		sampler_ptr = NULL;
		sampler_single_ptr = new sampler_single(1);
		fog_ptr = NULL;
		set_ambient(color_white / 5);
	}

	world::~world() {
		delete tracer_ptr;
		delete sampler_single_ptr;
	}

	bool world::get_hit(const ray &emission_ray, hitInfo *info_ptr) {
		bool hit_flag = false;
		static hitInfo temp;
		surface *surface_ptr;

		info_ptr->hit_t = huge_double;
		hit_flag = false;
		for (std::vector<surface *>::iterator iter = surfaces.begin(); iter != surfaces.end(); ++iter) {
			surface_ptr = (*iter);
			if (surface_ptr->hit(emission_ray, 0, &temp)) {
				if (temp.hit_t > epsilon && temp.hit_t < info_ptr->hit_t) {
					info_ptr->hit_t = temp.hit_t;
					info_ptr->surface_ptr = surface_ptr;
					hit_flag = true;
				}
			}
		}
		if (hit_flag) { 
			info_ptr->hit_point = emission_ray.get_origin() + emission_ray.get_dir() * info_ptr->hit_t;
			info_ptr->hit_relative_point = info_ptr->surface_ptr->get_relative_pos(info_ptr->hit_point);
			info_ptr->normal = info_ptr->surface_ptr->get_normal(info_ptr->hit_point);
			info_ptr->world_ptr = this;
			info_ptr->emission_ray = emission_ray;
		}
		return hit_flag;
	}

	void world::render_scene() {
		int *buffer_ptr = pixal_buffer_ptr;
		colorRGB color;
		point2D sample_point;
		int number_samples = get_sampler()->get_sampler_count();

		for (int y = 0; y < dest_h; y += 1) {
			for (int x = 0; x < dest_w; x += 1) {
				color = color_black;
				for (int i = 0; i < number_samples; i += 1) {
					get_sampler()->next_sampler();
					sample_point = get_sampler()->get_sampler_unit(sampler_set_anti_aliasing);
					color += camera_ptr->render_scene(x + sample_point.x, y + sample_point.y, dest_w, dest_h, this);
				}
				color = color / number_samples;
				*buffer_ptr ++ = color.clamp_to_int();
			}
		}
	}
}