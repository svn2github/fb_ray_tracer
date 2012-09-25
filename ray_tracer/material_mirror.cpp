
#include "material_mirror.hpp"
#include "hitInfo.hpp"

namespace ray_tracer {

	material_mirror::material_mirror() {
		mirror_ptr = new BRDF_mirror;
		diffuse_ptr = new BRDF_lambertian;
		set_mirror_coefficient(color_white);
	}

	material_mirror::~material_mirror() {
		delete mirror_ptr;
		delete diffuse_ptr;
	}

	colorRGB material_mirror::material_shade(hitInfo *info_ptr, const colorRGB &surface_color, const vector3D &win, const vector3D &wout) {
		return mirror_ptr->reflect_f(info_ptr, wout) + diffuse_ptr->f(info_ptr, win, wout) * surface_color;
	}
}