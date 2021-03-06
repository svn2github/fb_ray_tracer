
#include "surface.hpp"

namespace ray_tracer {

	surface::surface() {
		bounding_surface_ptr = NULL;
		attached_surface_ptr = NULL;
		material_ptr = NULL;
		texture_ptr = NULL;
		bifaced = false;
		clear_transformation();
	}

	surface::~surface() { }

	void surface::attach(const surface *attached_surface_ptr_) {
		attached_surface_ptr = attached_surface_ptr_;
	}

	double surface::hit(const ray &emission_ray, const surface **hit_surface_ptr) const {
		return -1;
	}

	vector3D surface::atnormal(const point3D &point) const {
		return vector3D(0, 0, 1);
	}

	void surface::set_material(const material *material_ptr_) {
		material_ptr = material_ptr_;
	}

	void surface::set_texture(const texture *texture_ptr_) {
		texture_ptr = texture_ptr_;
	}

	void surface::set_bifaced(bool twoface_) {
		bifaced = twoface_;
	}

	void surface::set_transform_center(const point3D &center_) {
		transform_center = center_;
	}

	void surface::clear_transformation() {
		transformed = false;
		transform_center = point3D(0, 0, 0);
		transform = transformation();
	}

	void surface::apply_transformation(const transformation &transform_) {
		transformed = true;
		transform = transform_ * transform;
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
