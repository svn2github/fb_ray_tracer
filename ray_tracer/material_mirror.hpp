#ifndef __MATERIAL_MIRROR_HPP
#define __MATERIAL_MIRROR_HPP

#include "material.hpp"
#include "BRDF.hpp"
#include "BRDF_mirror.hpp"
#include "BRDF_lambertian.hpp"

namespace ray_tracer {
	class material_mirror : public material  {
	public:
		material_mirror();
		~material_mirror();
		colorRGB material_shade(hitInfo *, const colorRGB &, const vector3D &, const vector3D &);
		void set_mirror_coefficient(const colorRGB &);
	private:
		BRDF_mirror *mirror_ptr;
		BRDF_lambertian *diffuse_ptr;
	};

	inline void material_mirror::set_mirror_coefficient(const colorRGB &coefficient_) {
		mirror_ptr->set_coefficient(coefficient_);
		diffuse_ptr->set_coefficient(coefficient_);
	}
}

#endif