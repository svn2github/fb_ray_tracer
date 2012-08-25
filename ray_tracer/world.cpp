
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

		for (int y = 0; y < dest_h; y += 1) {
			for (int x = 0; x < dest_w; x += 1) {			
				ray camera_ray = image_ptr->get_ray(x, y, dest_w, dest_h, camera_ptr);
				colorRGB color, color_final;
				int r = 0, g = 0, b = 0;
				for (std::vector<surface *>::iterator iter = surfaces_ptr.begin(); iter != surfaces_ptr.end(); ++iter) {
					if (tracer_ptr->ray_color(this, *iter, &camera_ray, &color)) {
						color_final += color;
					}
				}
				*buffer_ptr ++ = color_final.clamp();
			}
		}
	}
}