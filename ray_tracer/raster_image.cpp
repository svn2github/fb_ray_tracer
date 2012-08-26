
#include "raster_image.hpp"

namespace ray_tracer {

	raster_image::raster_image() {
		set_left(0);
		set_right(0);
		set_top(0);
		set_bottom(0);
	}

	raster_image::raster_image(double left_, double right_, double top_, double bottom_) {
		set_left(left_);
		set_right(right_);
		set_top(top_);
		set_bottom(bottom_);
	}
}