#ifndef __MATERIAL_MATTE_HPP__
#define __MATERIAL_MATTE_HPP__

#include "material.hpp"
#include "BRDF.hpp"
#include "BRDF_lambertian.hpp"

namespace ray_tracer {
	class material_matte : public material  {
	public:
		material_matte();
		material_matte(const colorRGB &);
		~material_matte();
		colorRGB material_shade(hitInfo *, const colorRGB &, const vector3D &, const vector3D &) const;
	private:
		BRDF_lambertian *diffuse_ptr;
	};
}

#endif