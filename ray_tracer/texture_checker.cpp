
#include "texture_checker.hpp"

namespace ray_tracer {

	texture_checker::texture_checker() {
		color1 = color_black;
		color2 = color_white;
	}

	texture_checker::texture_checker(colorRGB color1_, colorRGB color2_) {
		color1 = color1_;
		color2 = color2_;
	}

	colorRGB texture_checker::texture_shade(hitInfo *info_ptr) {
		const int sz = 4;
		const double huge = 10000;
		point3D p = info_ptr->hit_point;
		int x = (p.x + huge) / sz, y = (p.y + huge) / sz, z = (p.z + huge) / sz, mod;
	
		mod = (((x + y + z) % 2) + 2) % 2;
		if (mod) {
			return color1;
		} else {
			return color2;
		}
	}
}
