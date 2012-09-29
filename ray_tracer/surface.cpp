
#include "surface.hpp"

namespace ray_tracer {

	surface::surface() {
		material_ptr = NULL;
		texture_ptr = NULL;
		twoface_shading = false;
	}

	surface::~surface() { }

	double surface::hit(const ray &emission_ray) const {
		return -1;
	}

	vector3D surface::get_normal_vector(const point3D &point) const {
		return vector3D(0, 0, 1);
	}

	point3D surface::get_local_point(const point3D &point) const {
		return point3D(0, 0, 0);
	}

	void surface::enable_twoface_shading(bool twoface_) {
		twoface_shading = twoface_;
	}

	colorRGB surface::material_shade(hitInfo *info_ptr, const colorRGB &surface_color, const vector3D &win, const vector3D &wout) const {
		return material_ptr->material_shade(info_ptr, surface_color, win, wout);
	}

	colorRGB surface::texture_shade(hitInfo *info_ptr) const {
		return texture_ptr->texture_shade(info_ptr);
	}
}
