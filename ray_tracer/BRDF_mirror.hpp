#ifndef __BRDF_MIRROR_HPP__
#define __BRDF_MIRROR_HPP__

#include "BRDF.hpp"

namespace ray_tracer {
	class BRDF_mirror : public BRDF {
	public:
		colorRGB f(hitInfo *, const vector3D &, const vector3D &) const;
		colorRGB reflect_f(hitInfo *, const vector3D &) const;
	};
}

#endif