
#include "world.hpp"
#include "ray.hpp"
#include "vector3D.hpp"
#include "light.hpp"
#include "surface.hpp"
#include "raster_image.hpp"
#include "ray_tracer.hpp"
#include "hit_record.hpp"

namespace ray_tracer {

	world::world() {
		tracer_ptr = new ray_tracer;
	}

	world::~world() {
		delete tracer_ptr;
	}

	void world::add_light(light *light_ptr_) {
		lights_ptr.push_back(light_ptr_);
	}

	void world::add_surface(surface *surface_ptr_) {
		surfaces_ptr.push_back(surface_ptr_);
	}

	void world::set_camera(camera *camera_ptr_) {
		camera_ptr = camera_ptr_;
	}

	void world::set_raster_image(raster_image *image_ptr_) {
		image_ptr = image_ptr_;
	}

	void world::fit_window(int w, int h, void *p) {
		dest_w = w;
		dest_h = h;
		pixal_buffer_ptr = (int *)p;
	}

	void world::render_scene() {
		int *buffer_ptr = pixal_buffer_ptr;
		ray ray_from_camera;
		colorRGB color;
		hit_record record, t_record;
		bool hit_flag;

		for (int y = 0; y < dest_h; y += 1) {
			for (int x = 0; x < dest_w; x += 1) {
				ray_from_camera = image_ptr->get_ray(x, y, dest_w, dest_h, camera_ptr);
				record.hit_t = ray_huge_double;
				hit_flag = false;
				for (std::vector<surface *>::iterator iter = surfaces_ptr.begin(); iter != surfaces_ptr.end(); ++iter) {
					if ((*iter)->hit(&ray_from_camera, 0, &t_record)) {
						if (t_record.hit_t < record.hit_t) {
							record.hit_t = t_record.hit_t;
							record.surface_ptr = (*iter);
							hit_flag = true;
						}
					}
				}
				if (hit_flag) { 
					record.hit_point = ray_from_camera.start + ray_from_camera.dir * record.hit_t;
					record.normal = record.surface_ptr->get_normal(&record.hit_point);
					record.ray_ptr = &ray_from_camera;
					color = tracer_ptr->ray_color(this, &record);
				} else {
					color = color_black; // background color
				}
				*buffer_ptr ++ = color.clamp();
			}
		}
	}
}