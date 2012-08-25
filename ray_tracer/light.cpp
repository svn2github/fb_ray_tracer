
#include "light.hpp"

namespace ray_tracer {
	
	light::light() {
		position = point3D();
		color = color_white;
	}

	light::light(const point3D &position_, const colorRGB &color_) {
		position = position_;
		color = color_;
	}	
};
