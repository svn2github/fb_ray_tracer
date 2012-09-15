
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

	bool light_point::under_shadow(hitInfo *info_ptr) const {
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
};
