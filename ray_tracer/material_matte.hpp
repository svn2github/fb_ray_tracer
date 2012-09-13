#ifndef __MATERIAL_MATTE_HPP
#define __MATERIAL_MATTE_HPP

#include "material.hpp"
#include "BRDF.hpp"
#include "BRDF_lambertian.hpp"

namespace ray_tracer {
	class material_matte : public material  {
	public:
		material_matte();
		~material_matte();
		colorRGB material_shade(hitInfo *, const colorRGB &, const vector3D &, const vector3D &);
		void set_diffuse_coefficient(const colorRGB &);
	private:
		BRDF_lambertian *diffuse_ptr;
	};

	inline void material_matte::set_diffuse_coefficient(const colorRGB &coefficient_) {
		diffuse_ptr->set_coefficient(coefficient_);
	}
}

#endif