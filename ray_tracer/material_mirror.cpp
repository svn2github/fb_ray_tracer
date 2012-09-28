
#include "material_mirror.hpp"
#include "hitInfo.hpp"

namespace ray_tracer {

	material_mirror::material_mirror() {
		reflection_ptr = new BRDF_reflection(color_white);
		diffuse_ptr = new BRDF_lambertian(color_white);
	}

	material_mirror::material_mirror(const colorRGB &rho_) {
		reflection_ptr = new BRDF_reflection(rho_);
		diffuse_ptr = new BRDF_lambertian(rho_);
	}

	material_mirror::~material_mirror() {
		delete reflection_ptr;
		delete diffuse_ptr;
	}

	colorRGB material_mirror::material_shade(hitInfo *info_ptr, const colorRGB &surface_color, const vector3D &win, const vector3D &wout) const {
		return (reflection_ptr->reflect_f(info_ptr, wout) + diffuse_ptr->f(info_ptr, win, wout)) * surface_color;
	}
}