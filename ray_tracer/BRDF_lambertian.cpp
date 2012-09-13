
#include "BRDF_lambertian.hpp"

namespace ray_tracer {
	colorRGB BRDF_lambertian::f(hitInfo *hit_ptr, const vector3D &win, const vector3D &wout) {
		return coefficient;
	}
}
