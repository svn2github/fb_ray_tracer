
#include "BRDF_phong.hpp"
#include "vector3D.hpp"
#include "misc.hpp"

namespace ray_tracer {

	colorRGB BRDF_phong::f(hitInfo *info_ptr, const vector3D &win, const vector3D &wout) const {
		double temp;

		temp = info_ptr->normal * (win + wout).normalized();
		if (temp > 0.0) {
			temp = pow(temp, shininess);
			return colorRGB(temp, temp, temp) * coefficient;
		} else {
			return color_black;
		}
	}
}
