
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

	void world::fit_window(int w, int h, void *p) {
		dest_w = w;
		dest_h = h;
		pixal_buffer_ptr = (int *)p;
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
			info_ptr->emission_ray = emission_ray;
		}
		return hit_flag;
	}

	void world::render_begin() {
		curr_rendering_x = 0;
		curr_rendering_y = 0;
		rendering_mutex = 0;
	}

	void world::render_scene() {
		colorRGB color;
		point2D sample_point;
		int x, y;
		
		while (curr_rendering_y != dest_h) {
			while (rendering_mutex) { }
			rendering_mutex = 1;
			x = curr_rendering_x;
			y = curr_rendering_y;
			x += 1;
			if (x == dest_w) {
				x = 0; 
				y += 1;
			}
			curr_rendering_x = x;
			curr_rendering_y = y;
			rendering_mutex = 0;
			color = color_black;

			sampler_iterator sam_iter(sampler_ptr == NULL ? sampler_single_ptr : sampler_ptr);
			int number_sample = sam_iter.get_sampler_count();

			for (int i = 0; i < number_sample; i += 1) {
				hitInfo info;
				
				info.world_ptr = this;
				info.sampler_iterator_ptr = &sam_iter;
				sam_iter.next_sampler();
				sample_point = sam_iter.get_sampler_unit(sampler_set_anti_aliasing);
				color += camera_ptr->render_scene(x + sample_point.x, y + sample_point.y, dest_w, dest_h, &info);
			}
			color = color / number_sample;
			*(pixal_buffer_ptr + y * dest_w + x) = color.clamp_to_int();
		}
	}
}