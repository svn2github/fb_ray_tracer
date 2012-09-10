#ifndef __BRDF_LAMBERTIAN_HPP
#define __BRDF_LAMBERTIAN_HPP

#include "BRDF.hpp"

namespace ray_tracer {
	class BRDF_lambertian : public BRDF {
	public:
		colorRGB f(hit_info *, const vector3D &, const vector3D &);
	};
}

#endif