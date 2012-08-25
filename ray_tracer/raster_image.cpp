
#include "raster_image.hpp"
#include "colorRGB.hpp"
#include "ray.hpp"
#include "surface.hpp"
#include "vector3D.hpp"
#include "world.hpp"
#include "ray_tracer.hpp"
#include "camera.hpp"
#include <vector>

namespace ray_tracer {

	raster_image::raster_image() {
		_l = _r = _t = _b = 0;
	}

	raster_image::raster_image(double l_, double r_, double t_, double b_) {
		_l = l_;
		_r = r_;
		_t = t_;
		_b = b_;
	}
	
	void raster_image::fit(int w, int h, void *p) {
		_dest_w = w;
		_dest_h = h;
		_pixal_buffer_ptr = (int *)p;
	}

	ray raster_image::get_ray(int x, int y, camera *camera_ptr) {
		if (x < 0 || x >= _dest_w || y < 0 || y >= _dest_h) {
			throw "coordinate out of rectangle bound.";
		} else {
			 double u = _l + (_r - _l) * ((double)x + 0.5) / (double)_dest_w;
			 double v = _b + (_t - _b) * ((double)y + 0.5) / (double)_dest_h;
			 point3D origin;
			 vector3D dir;
			 dir = -camera_ptr->_axis_w;
			 origin = camera_ptr->_position + u * camera_ptr->_axis_u + v * camera_ptr->_axis_v;
			 return ray(origin, dir);
		}
	}
	
	void raster_image::render_scene(world *world_ptr, ray_tracer *tracer_ptr, camera *camera_ptr) {
		int *buffer_ptr = _pixal_buffer_ptr;

		for (int y = 0; y < _dest_h; y += 1) {
			for (int x = 0; x < _dest_w; x += 1) {			
				ray camera_ray = get_ray(x, y, camera_ptr);
				colorRGB color, color_final;
				int r = 0, g = 0, b = 0;
				for (std::vector<surface *>::iterator iter = world_ptr->surfaces_ptr.begin(); iter != world_ptr->surfaces_ptr.end(); ++iter) {
					if (tracer_ptr->ray_color(this, world_ptr, *iter, &camera_ray, &color)) {
						color_final += color;
					}
				}
				*buffer_ptr ++ = color_final.clamp();
			}
		}
	}
}