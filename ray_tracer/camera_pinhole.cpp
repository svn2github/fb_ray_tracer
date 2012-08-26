
#include "camera_pinhole.hpp"

namespace ray_tracer {
	
	camera_pinhole::camera_pinhole() {
		eye = point3D();
		lookat = point3D();
		up = vector3D();
		compute_axis();
	}

	camera_pinhole::camera_pinhole(const point3D &eye_, const point3D &lookat_, const vector3D &up_) {
		eye = eye_;
		lookat = lookat_;
		up = up_;
		compute_axis();
	}
	
	ray camera_pinhole::get_ray(int x, int y, int w, int h, raster_image *image_ptr) const {
		double u = image_ptr->get_left() + (image_ptr->get_right() - image_ptr->get_left()) * ((double)x + 0.5) / (double)w;
		double v = image_ptr->get_bottom() + (image_ptr->get_top() - image_ptr->get_bottom()) * ((double)y + 0.5) / (double)h;
		point3D origin;
		vector3D dir;

		dir = lookat - eye + u * axis_u + v * axis_v;
		origin = eye;
		return ray(origin, dir);
	}
}