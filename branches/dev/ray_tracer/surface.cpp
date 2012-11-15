
#include "surface.hpp"

namespace ray_tracer {

	surface::surface() {
		bounding_surface_ptr = NULL;
		attached_surface_ptr = NULL;
		material_ptr = NULL;
		texture_ptr = NULL;
		twoface_shading = false;
	}

	surface::~surface() { }

	void surface::attach(const surface *attached_surface_ptr_) {
		attached_surface_ptr = attached_surface_ptr_;
	}

	double surface::hit(const ray &emission_ray, const surface **hit_surface_ptr) const {
		return -1;
	}

	vector3D surface::get_normal_vector(const point3D &point) const {
		return vector3D(0, 0, 1);
	}

	point3D surface::get_local_point(const point3D &point) const {
		return point3D(0, 0, 0);
	}

	void surface::set_twoface_shading(bool twoface_) {
		twoface_shading = twoface_;
	}

	void surface::set_material(const material *material_ptr_) {
		material_ptr = material_ptr_;
	}

	void surface::set_texture(const texture *texture_ptr_) {
		texture_ptr = texture_ptr_;
	}

	colorRGB surface::material_shade(hitInfo *info_ptr, const colorRGB &surface_color, const vector3D &win, const vector3D &wout) const {
		if (attached_surface_ptr != NULL) {
			return attached_surface_ptr->material_shade(info_ptr, surface_color, win, wout);
		} else {
			return material_ptr->material_shade(info_ptr, surface_color, win, wout);
		}
	}

	colorRGB surface::texture_shade(hitInfo *info_ptr) const {
		if (attached_surface_ptr != NULL) {
			return attached_surface_ptr->texture_shade(info_ptr);
		} else {
			return texture_ptr->texture_shade(info_ptr);
		}
	}
}
