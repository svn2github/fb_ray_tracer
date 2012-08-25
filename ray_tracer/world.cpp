
#include "world.hpp"
#include "ray.hpp"
#include "vector3D.hpp"
#include "light.hpp"
#include "surface.hpp"
#include "raster_image.hpp"
#include "ray_tracer.hpp"

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
		ray camera_ray;
		colorRGB color;
		double min_t, hit_t;
		point3D contact_point, hit_contact_point;
		surface *surface_ptr;

		for (int y = 0; y < dest_h; y += 1) {
			for (int x = 0; x < dest_w; x += 1) {			
				camera_ray = image_ptr->get_ray(x, y, dest_w, dest_h, camera_ptr);
				min_t = ray_huge_double;
				surface_ptr = NULL;
				for (std::vector<surface *>::iterator iter = surfaces_ptr.begin(); iter != surfaces_ptr.end(); ++iter) {
					hit_t = 0;
					if ((*iter)->hit(&camera_ray, &hit_t, &hit_contact_point)) {
						if (hit_t < min_t) {
							min_t = hit_t;
							contact_point = hit_contact_point;
							surface_ptr = (*iter);
						}
					}
				}
				if (surface_ptr != NULL) { 
					color = tracer_ptr->ray_color(this, surface_ptr, &camera_ray, &contact_point);
				} else {
					color = color_black; // background color
				}
				*buffer_ptr ++ = color.clamp();
			}
		}
	}
}