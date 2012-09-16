#ifndef __LIGHT_HPP
#define __LIGHT_HPP

#include "point3D.hpp"
#include "colorRGB.hpp"
#include "hitInfo.hpp"
#include "ray.hpp"

namespace ray_tracer {
	class light {
	public:
		virtual ~light();
		point3D get_position() const;
		void set_position(const point3D &);
		void set_color(const colorRGB &);
		virtual colorRGB light_shade(hitInfo *) const;
		virtual bool in_range(hitInfo *) const;
		virtual bool under_shadow(hitInfo *) const;
	protected:
		point3D position;
		colorRGB color;
	};

	inline point3D light::get_position() const {
		return position;
	}

	inline void light::set_position(const point3D &position_) {
		position = position_;
	}

	inline void light::set_color(const colorRGB &color_) {
		color = color_;
	}
}

#endif