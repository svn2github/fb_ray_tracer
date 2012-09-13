
#include "surface.hpp"

namespace ray_tracer {

	surface::~surface() { }

	bool surface::hit(ray *ray_ptr, double tmin, hitInfo *info_ptr) const {
		return false;
	}

	vector3D surface::get_normal(const point3D &point) const {
		return vector3D();
	}

	point3D surface::get_relative_pos(const point3D &point) const {
		return point3D();
	}

	colorRGB surface::material_shade(hitInfo *info_ptr, const colorRGB &surface_color, const vector3D &win, const vector3D &wout) {
		return material_ptr->material_shade(info_ptr, surface_color, win, wout);
	}

	colorRGB surface::texture_shade(hitInfo *info_ptr) {
		return texture_ptr->texture_shade(info_ptr);
	}
}
