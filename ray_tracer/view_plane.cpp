
#include "view_plane.hpp"

namespace ray_tracer {

	view_plane::view_plane() {
		set_left(0);
		set_right(0);
		set_top(0);
		set_bottom(0);
	}

	view_plane::view_plane(double left_, double right_, double top_, double bottom_) {
		set_left(left_);
		set_right(right_);
		set_top(top_);
		set_bottom(bottom_);
	}
}