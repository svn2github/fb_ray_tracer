#ifndef __MATERIAL_BLINN_PHONG_HPP
#define __MATERIAL_BLINN_PHONG_HPP

#include "material.hpp"
#include "BRDF.hpp"
#include "BRDF_lambertian.hpp"
#include "BRDF_blinn_phong.hpp"

namespace ray_tracer {
	class material_blinn_phong : public material  {
	public:
		material_blinn_phong();
		~material_blinn_phong();
		colorRGB material_shade(hitInfo *, const colorRGB &, const vector3D &, const vector3D &);
		void set_diffuse_coefficient(const colorRGB &);
		void set_specular_coefficient(const colorRGB &);
		void set_specular_shininess(const int &);
	private:
		BRDF_lambertian *diffuse_ptr;
		BRDF_blinn_phong *specular_ptr;
	};

	inline void material_blinn_phong::set_diffuse_coefficient(const colorRGB &coefficient_) {
		diffuse_ptr->set_coefficient(coefficient_);
	}

	inline void material_blinn_phong::set_specular_coefficient(const colorRGB &coefficient_) {
		specular_ptr->set_coefficient(coefficient_);
	}

	inline void material_blinn_phong::set_specular_shininess(const int &shininess_) {
		specular_ptr->set_shininess(shininess_);
	}
}

#endif