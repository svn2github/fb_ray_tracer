
#include "light.hpp"
#include "world.hpp"
#include <vector>

namespace ray_tracer {
	
	light::light() {
		set_position(point3D());
		set_color(color_white);
	}

	light::light(const point3D &position_, const colorRGB &color_) {
		set_position(position_);
		set_color(color_);
	}

	bool light::under_shadow(hitInfo *info_ptr) const {
		world *world_ptr = info_ptr->world_ptr;
		point3D origin = info_ptr->hit_point;
		vector3D dir;
		hitInfo temp;
		double dist;

		dir = position - origin;
		dist = dir.length();
		dir = dir.normalized();
		if (world_ptr->get_hit(&ray(origin, dir), &temp)) {
			return (temp.hit_t < dist);
		} else {
			return false;
		}
	}
};
