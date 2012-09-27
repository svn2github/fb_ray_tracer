
#include "ray.hpp"
#include "light.hpp"
#include "surface.hpp"
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

	bool world::get_hit(const ray &emission_ray, hitInfo *info_ptr) const {
		bool hit_flag = false;
		const surface *surface_ptr;

		info_ptr->hit_time = huge_double;
		hit_flag = false;
		for (std::vector<const surface *>::const_iterator iter = surfaces.begin(); iter != surfaces.end(); ++iter) {
			surface_ptr = *iter;
			double t = surface_ptr->hit(emission_ray);
			/* Avoid hiting the surface which shots this ray */
			if (t > epsilon && t < info_ptr->hit_time) {
				info_ptr->hit_time = t;
				info_ptr->surface_ptr = surface_ptr;
				hit_flag = true;
			}
		}
		if (hit_flag) { 
			info_ptr->hit_point = emission_ray.origin + emission_ray.dir * info_ptr->hit_time;
			info_ptr->hit_relative_point = info_ptr->surface_ptr->get_relative_pos(info_ptr->hit_point);
			info_ptr->normal = info_ptr->surface_ptr->get_normal(info_ptr->hit_point);
			info_ptr->emission_ray = emission_ray;
		}
		return hit_flag;
	}

	void world::render_begin(int w_, int h_, void *ptr_) {
		dest_w = w_;
		dest_h = h_;
		pixal_buffer_ptr = (int *)ptr_;
		current_coordinate_x = 0;
		current_coordinate_y = 0;
	}

	void world::render_scene() {
		colorRGB color;
		point2D sample_point;
		int x, y;
		hitInfo info;

		while (current_coordinate_y < dest_h) {
#ifndef __MT_NO_MUTEX
			coordinate_mutex.lock();
#endif
			x = current_coordinate_x + 1;
			y = current_coordinate_y;
			if (x == dest_w) {
				x = 0; 
				y += 1;
			}
			current_coordinate_x = x;
			current_coordinate_y = y;
#ifndef __MT_NO_MUTEX
			coordinate_mutex.unlock();
#endif
			sampler_iterator sam_iter(sampler_ptr == NULL ? sampler_single_ptr : sampler_ptr);
			int number_sample = sam_iter.get_sampler_count();

			color = color_black;
			for (int i = 0; i < number_sample; i += 1) {
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
