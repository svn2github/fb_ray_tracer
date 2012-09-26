
#include "BRDF.hpp"

namespace ray_tracer {

	BRDF::BRDF() {
		coefficient = color_white;
	}

	colorRGB BRDF::f(hitInfo *info_ptr, const vector3D &win, const vector3D &wout) const {
		return coefficient;
	}

	colorRGB BRDF::reflect_f(hitInfo *info_ptr, const vector3D &win) const {
		return color_black;
	}
}
