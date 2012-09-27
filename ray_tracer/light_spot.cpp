
#include "light_spot.hpp"
#include "world.hpp"

namespace ray_tracer {
	
	light_spot::light_spot() {
		set_direcion(vector3D(0, 0, 1));
		set_cutoff(pi / 2);
		set_exponent(1);
	}

	light_spot::light_spot(const point3D &position_, const colorRGB &color_, const vector3D &direction_, double cutoff_, int exponent_) : light(position_, color_) {
		set_direcion(direction_);
		set_cutoff(cutoff_);
		set_exponent(exponent_);
	}

	colorRGB light_spot::light_shade(hitInfo *info_ptr) const {
		colorRGB color = light::light_shade(info_ptr);
		vector3D v = (info_ptr->hit_point - position).normalized();
		vector3D d = direction;
		double vdotd = v * d;

		if (vdotd > 0) {
			return color * pow(vdotd, exponent);
		} else {
			return color_black;
		}
	}

	bool light_spot::in_range(hitInfo *info_ptr) const {
		vector3D v = (info_ptr->hit_point - position).normalized();
		vector3D d = direction;
		double vdotd = v * d;

		return (vdotd > cos_cutoff);
	}
}