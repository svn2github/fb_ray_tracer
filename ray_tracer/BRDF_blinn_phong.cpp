
#include "BRDF_blinn_phong.hpp"
#include "vector3D.hpp"
#include <cstdio>

namespace ray_tracer {
	colorRGB BRDF_blinn_phong::f(hit_info *hit_ptr, const vector3D &win, const vector3D &wout) {
		double temp;

		temp = hit_ptr->normal * (win + wout).normalized();
		if (temp > 0.0) {
			temp = pow(temp, shininess);
			return colorRGB(temp, temp, temp) * coefficient;
		} else {
			return color_black;
		}
	}
}
