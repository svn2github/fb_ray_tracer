
#include "surface.hpp"

namespace ray_tracer {

	surface::~surface() { }

	void surface::get_color(const point3D &p_ptr, colorRGB *color_ptr) const {
		*color_ptr = surface_color;
	}
}
