
#include "surface.hpp"

namespace ray_tracer {

	surface::~surface() { }

	colorRGB surface::material_shade(hit_info *info_ptr, const colorRGB &surface_color, const vector3D &win, const vector3D &wout) {
		return material_ptr->material_shade(info_ptr, surface_color, win, wout);
	}

	colorRGB surface::texture_shade(hit_info *info_ptr) {
		return texture_ptr->texture_shade(info_ptr);
	}
}
