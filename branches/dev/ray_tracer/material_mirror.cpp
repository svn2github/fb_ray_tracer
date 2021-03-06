
#include "material_mirror.hpp"
#include "hitInfo.hpp"

namespace ray_tracer {

	material_mirror::material_mirror() {
		reflection_ptr = std::unique_ptr<BRDF_reflection>(new BRDF_reflection(color_white));
		diffuse_ptr = std::unique_ptr<BRDF_lambertian>(new BRDF_lambertian(color_white));
	}

	material_mirror::material_mirror(const colorRGB &rho_) {
		reflection_ptr = std::unique_ptr<BRDF_reflection>(new BRDF_reflection(rho_));
		diffuse_ptr = std::unique_ptr<BRDF_lambertian>(new BRDF_lambertian(rho_));
	}

	colorRGB material_mirror::material_shade(hitInfo *info_ptr, const colorRGB &surface_color, const vector3D &win, const vector3D &wout) const {
		return (reflection_ptr->reflect_f(info_ptr, wout) + diffuse_ptr->f(info_ptr, win, wout)) * surface_color;
	}
}