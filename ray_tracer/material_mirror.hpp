#ifndef __MATERIAL_MIRROR_HPP__
#define __MATERIAL_MIRROR_HPP__

#include "material.hpp"
#include "BRDF.hpp"
#include "BRDF_reflection.hpp"
#include "BRDF_lambertian.hpp"

namespace ray_tracer {
	class material_mirror : public material  {
	public:
		material_mirror();
		material_mirror(const colorRGB &);
		~material_mirror();
		colorRGB material_shade(hitInfo *, const colorRGB &, const vector3D &, const vector3D &) const;
	private:
		BRDF_reflection *reflection_ptr;
		BRDF_lambertian *diffuse_ptr;
	};
}

#endif