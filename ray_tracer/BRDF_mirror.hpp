#ifndef __BRDF_MIRROR_HPP
#define __BRDF_MIRROR_HPP

#include "BRDF.hpp"

namespace ray_tracer {
	class BRDF_mirror : public BRDF {
	public:
		colorRGB f(hitInfo *, const vector3D &, const vector3D &);
		colorRGB reflect_f(hitInfo *, const vector3D &);
	};
}

#endif