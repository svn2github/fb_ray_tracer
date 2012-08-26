
#include "camera.hpp"
#include "raster_image.hpp"

namespace ray_tracer {

	camera::camera() { 
		position = point3D();
		axis_w = vector3D();
		axis_u = vector3D();
		axis_v = vector3D();
	}

	camera::camera(const point3D &position_, const vector3D &axis_w_, const vector3D &axis_u_) {
		position = position_;
		axis_w = axis_w_.normalized();
		axis_u = axis_u_.normalized();
		axis_v = axis_w ^ axis_u;
	}

	ray camera::get_ray(int x, int y, int w, int h, raster_image *image_ptr) {
		double u = image_ptr->l + (image_ptr->r - image_ptr->l) * ((double)x + 0.5) / (double)w;
		double v = image_ptr->b + (image_ptr->t - image_ptr->b) * ((double)y + 0.5) / (double)h;
		point3D origin;
		vector3D dir;

		dir = -axis_w;
		origin = position + u * axis_u + v * axis_v;
		return ray(origin, dir);
	}
}