
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
		l = r = t = b = 0;
	}

	raster_image::raster_image(double l_, double r_, double t_, double b_) {
		l = l_;
		r = r_;
		t = t_;
		b = b_;
	}

	ray raster_image::get_ray(int x, int y, int w, int h, camera *camera_ptr) {
		double u = l + (r - l) * ((double)x + 0.5) / (double)w;
		double v = b + (t - b) * ((double)y + 0.5) / (double)h;
		point3D origin;
		vector3D dir;
		dir = -camera_ptr->_axis_w;
		origin = camera_ptr->_position + u * camera_ptr->_axis_u + v * camera_ptr->_axis_v;
		return ray(origin, dir);
	}
}