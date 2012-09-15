
#include "light.hpp"

namespace ray_tracer {
	
	light::~light() { }

	bool light::under_shadow(hitInfo *info_ptr) const {
		return false;
	}

	bool light::in_range(hitInfo *info_ptr) const {
		return true;
	}
}
