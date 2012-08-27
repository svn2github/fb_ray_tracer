
#include "ray.hpp"
#include "light.hpp"
#include "surface.hpp"
#include "view_plane.hpp"
#include "tracer.hpp"
#include "camera.hpp"
#include "world.hpp"

namespace ray_tracer {

	world::world() {
		tracer_ptr = new tracer;
		set_ambient(color_white);
	}

	world::~world() {
		delete tracer_ptr;
	}

	bool world::get_hit(ray *ray_ptr, hit_info *info_ptr) {
		bool hit_flag = false;
		static hit_info temp;
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
			info_ptr->normal = info_ptr->surface_ptr->get_normal(info_ptr->hit_point);
			info_ptr->world_ptr = this;
			info_ptr->ray_ptr = ray_ptr;
		}
		return hit_flag;
	}

	void world::render_scene() {
		int *buffer_ptr = pixal_buffer_ptr;

		for (int y = 0; y < dest_h; y += 1) {
			for (int x = 0; x < dest_w; x += 1) {
				*buffer_ptr ++ = camera_ptr->render_scene(x, y, dest_w, dest_h, this).clamp_to_int();
			}
		}
	}
}