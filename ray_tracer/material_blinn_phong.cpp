
#include "material_blinn_phong.hpp"
#include "hitInfo.hpp"

namespace ray_tracer {

	material_blinn_phong::material_blinn_phong() {
		diffuse_ptr = new BRDF_lambertian;
		specular_ptr = new BRDF_blinn_phong;
		set_diffuse_coefficient(color_white);
		set_specular_coefficient(color_white);
		set_specular_shininess(1);
	}

	material_blinn_phong::~material_blinn_phong() {
		delete diffuse_ptr;
		delete specular_ptr;
	}

	colorRGB material_blinn_phong::material_shade(hitInfo *info_ptr, const colorRGB &surface_color, const vector3D &win, const vector3D &wout) {
		return diffuse_ptr->f(info_ptr, win, wout) * surface_color + specular_ptr->f(info_ptr, win, wout);
	}
}