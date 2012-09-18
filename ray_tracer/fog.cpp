
#include "fog.hpp"
#include "misc.hpp"

namespace ray_tracer {

	fog::fog() {
		density = 1;
		fog_color = color_white;
	}

	fog::fog(double density_, int exponent_, const colorRGB &fog_color_) {
		density = density_;
		exponent = exponent_;
		fog_color = fog_color_;
	}

	colorRGB fog::fog_blending(hitInfo *info_ptr, const point3D &origin, const colorRGB &color) {
		double z = (info_ptr->hit_point - origin).length();
		double f = exp(-pow(density * z, exponent));

		return f * color + (1 - f) * fog_color;
	}
}
