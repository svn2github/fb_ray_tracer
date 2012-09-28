
#include "surface.hpp"

namespace ray_tracer {

	surface::surface() {
		material_ptr = NULL;
		texture_ptr = NULL;
	}

	surface::~surface() { }

	bool surface::two_face() const {
		return true;
	}

	double surface::hit(const ray &emission_ray) const {
		return -1;
	}

	vector3D surface::get_normal(const point3D &point) const {
		return vector3D(0, 0, 1);
	}

	point3D surface::get_relative_pos(const point3D &point) const {
		return point3D(0, 0, 0);
	}

	colorRGB surface::material_shade(hitInfo *info_ptr, const colorRGB &surface_color, const vector3D &win, const vector3D &wout) const {
		return material_ptr->material_shade(info_ptr, surface_color, win, wout);
	}

	colorRGB surface::texture_shade(hitInfo *info_ptr) const {
		return texture_ptr->texture_shade(info_ptr);
	}
}
