
#include "world.hpp"
#include "ray.hpp"
#include "vector3D.hpp"
#include "light.hpp"
#include "surface.hpp"
#include "view_plane.hpp"
#include "ray_tracer.hpp"
#include "hit_record.hpp"

namespace ray_tracer {

	world::world() {
		tracer_ptr = new ray_tracer;
		set_ambient(color_white);
	}

	world::~world() {
		delete tracer_ptr;
	}

	void world::add_light(light *light_ptr_) {
		lights.push_back(light_ptr_);
	}

	void world::add_surface(surface *surface_ptr_) {
		surfaces.push_back(surface_ptr_);
	}

	void world::set_camera(camera *camera_ptr_) {
		camera_ptr = camera_ptr_;
	}

	void world::set_view_plane(view_plane *plane_ptr_) {
		plane_ptr = plane_ptr_;
	}

	void world::fit_window(int w, int h, void *p) {
		dest_w = w;
		dest_h = h;
		pixal_buffer_ptr = (int *)p;
	}

	bool world::get_hit_record(ray *ray_ptr, hit_record *record_ptr) {
		bool hit_flag = false;
		static hit_record temp_record;
		surface *surface_ptr;

		record_ptr->hit_t = huge_double;
		hit_flag = false;
		for (std::vector<surface *>::iterator iter = surfaces.begin(); iter != surfaces.end(); ++iter) {
			surface_ptr = (*iter);
			if (surface_ptr->hit(ray_ptr, 0, &temp_record)) {
				if (temp_record.hit_t < record_ptr->hit_t) {
					record_ptr->hit_t = temp_record.hit_t;
					record_ptr->surface_ptr = surface_ptr;
					hit_flag = true;
				}
			}
		}
		if (hit_flag) { 
			record_ptr->hit_point = ray_ptr->get_origin() + ray_ptr->get_dir() * record_ptr->hit_t;
			record_ptr->normal = record_ptr->surface_ptr->get_normal(&record_ptr->hit_point);
			record_ptr->world_ptr = this;
			record_ptr->ray_ptr = ray_ptr;
		}
		return hit_flag;
	}

	void world::render_scene() {
		int *buffer_ptr = pixal_buffer_ptr;
		ray ray;
		colorRGB color;
		hit_record record;

		for (int y = 0; y < dest_h; y += 1) {
			for (int x = 0; x < dest_w; x += 1) {
				ray = camera_ptr->get_ray(x, y, dest_w, dest_h, plane_ptr);
				if (get_hit_record(&ray, &record)) {
					color = tracer_ptr->ray_color(this, &record);
				} else {
					color = color_black; // background color
				}
				*buffer_ptr ++ = color.clamp_to_int();
			}
		}
	}
}