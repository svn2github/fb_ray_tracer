
#include "light_point.hpp"
#include "world.hpp"
#include <vector>

namespace ray_tracer {
	
	light_point::light_point() {
		set_position(point3D());
		set_color(color_white);
	}

	light_point::light_point(const point3D &position_, const colorRGB &color_) {
		set_position(position_);
		set_color(color_);
	}
};
