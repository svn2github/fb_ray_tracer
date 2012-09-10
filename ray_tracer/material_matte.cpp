
#include "material_matte.hpp"
#include "hit_info.hpp"

namespace ray_tracer {

	material_matte::material_matte() {
		diffuse_ptr = new BRDF_lambertian;
		set_diffuse_coefficient(color_white);
	}

	material_matte::~material_matte() {
		delete diffuse_ptr;
	}

	colorRGB material_matte::material_shade(hit_info *info_ptr, const colorRGB &surface_color, const vector3D &win, const vector3D &wout) {
		return diffuse_ptr->f(info_ptr, win, wout) * surface_color;
	}
}