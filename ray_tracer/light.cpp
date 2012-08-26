
#include "light.hpp"

namespace ray_tracer {
	
	light::light() {
		set_position(point3D());
		set_color(color_white);
	}

	light::light(const point3D &position_, const colorRGB &color_) {
		set_position(position_);
		set_color(color_);
	}	
};
