
#include "texture_checker.hpp"

namespace ray_tracer {

	colorRGB texture_checker::texture_shade(hit_info *info_ptr) {
		const int sz = 4;
		const double huge = 10000;
		point3D p = info_ptr->hit_point;
		int x = (p.x + huge) / sz, y = (p.y + huge) / sz, z = (p.z + huge) / sz, mod;
	
		mod = (((x + y + z) % 2) + 2) % 2;
		if (mod) {
			return color_black;
		} else {
			return color_white;
		}
	}
}
