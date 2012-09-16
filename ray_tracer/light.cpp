
#include "light.hpp"
#include "world.hpp"

namespace ray_tracer {
	
	light::~light() { }

	colorRGB light::light_shade(hitInfo *info_ptr) const {
		return color;
	}

	bool light::under_shadow(hitInfo *info_ptr) const {
		world *world_ptr = info_ptr->world_ptr;
		vector3D dir;
		hitInfo temp;
		double dist;

		dir = info_ptr->hit_point - position;
		dist = dir.length();
		dir = dir.normalized();
		if (world_ptr->get_hit(&ray(position, dir), &temp)) {
			return dblcmp(temp.hit_t - dist) < 0;
		} else {
			return false;
		}
	}

	bool light::in_range(hitInfo *info_ptr) const {
		return true;
	}
}
