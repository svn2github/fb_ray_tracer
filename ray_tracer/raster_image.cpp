
#include "raster_image.hpp"
#include "ray.hpp"
#include "camera.hpp"

namespace ray_tracer {

	raster_image::raster_image() {
		l = 0;
		r = 0;
		t = 0;
		b = 0;
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

		dir = -camera_ptr->axis_w;
		origin = camera_ptr->position + u * camera_ptr->axis_u + v * camera_ptr->axis_v;
		return ray(origin, dir);
	}
}