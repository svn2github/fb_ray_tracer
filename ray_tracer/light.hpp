#ifndef __LIGHT_HPP
#define __LIGHT_HPP

#include "point3D.hpp"
#include "colorRGB.hpp"
#include "hit_info.hpp"
#include "ray.hpp"

namespace ray_tracer {
	class light {
	public:
		light();
		light(const point3D &, const colorRGB &);
		point3D get_position() const;
		void set_position(const point3D &);
		colorRGB get_color() const;
		void set_color(const colorRGB &);
		bool under_shadow(hit_info *) const;
	private:
		point3D position;
		colorRGB color;
	};

	inline point3D light::get_position() const {
		return position;
	}

	inline void light::set_position(const point3D &position_) {
		position = position_;
	}

	inline colorRGB light::get_color() const {
		return color;
	}

	inline void light::set_color(const colorRGB &color_) {
		color = color_;
	}
}

#endif