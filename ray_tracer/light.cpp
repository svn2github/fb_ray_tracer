
#include "light.hpp"
#include "world.hpp"
#include <iostream>

namespace ray_tracer {
	
	void light::init_attenuation() {
		attenuation_enabled = false;
		attenuation_constant = 1;
		attenuation_linear = 0;
		attenuation_quadratic = 0;
	}

	light::light() {
		set_position(point3D(0, 0, 0));
		set_color(color_white);
		init_attenuation();
		cast_shadow = true;
	}

	light::light(const point3D &position_, const colorRGB &color_, bool shadow_) {
		set_position(position_);
		set_color(color_);
		cast_shadow = shadow_;
		init_attenuation();
	}

	light::~light() { }

	point3D light::get_light_origin(hitInfo *info_ptr) const {
		return position;
	}

	colorRGB light::light_shade(hitInfo *info_ptr) const {
		if (attenuation_enabled) {
			double d = (info_ptr->hit_point - info_ptr->light_position).length();
			double f = 1 / (attenuation_constant + attenuation_linear * d + attenuation_quadratic * d * d);

			return f * color;
		} else {
			return color;
		}
	}

	bool light::under_shadow(hitInfo *info_ptr) const {
		if (!cast_shadow) {
			return false;
		} else {
			world *world_ptr = info_ptr->world_ptr;
			vector3D dir;
			hitInfo temp;
			double dist;

			dir = info_ptr->hit_point - info_ptr->light_position;
			dist = dir.length();
			dir = dir.normalized();
			if (world_ptr->get_hit(ray(info_ptr->light_position, dir), &temp)) {
				return dblcmp(temp.hit_t - dist) < 0;
			} else {
				return false;
			}
		}
	}

	bool light::in_range(hitInfo *info_ptr) const {
		return true;
	}
}
