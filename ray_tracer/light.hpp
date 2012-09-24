#ifndef __LIGHT_HPP
#define __LIGHT_HPP

#include "point3D.hpp"
#include "colorRGB.hpp"
#include "hitInfo.hpp"
#include "ray.hpp"

namespace ray_tracer {
	class light {
	public:
		light();
		light(const point3D &, const colorRGB &, bool);
		virtual ~light();
		virtual point3D get_light_origin(hitInfo *) const;
		void set_position(const point3D &);
		void set_color(const colorRGB &);
		void set_attenuation_constant(const double &);
		void set_attenuation_linear(const double &);
		void set_attenuation_quadratic(const double &);
		bool under_shadow(hitInfo *) const;
		virtual colorRGB light_shade(hitInfo *) const;
		virtual bool in_range(hitInfo *) const;
	private:
		void init_attenuation();
	protected:
		point3D position;
		colorRGB color;
	private:
		bool cast_shadow;
		bool attenuation_enabled;
		double attenuation_constant, attenuation_linear, attenuation_quadratic;
	};

	inline void light::set_position(const point3D &position_) {
		position = position_;
	}

	inline void light::set_color(const colorRGB &color_) {
		color = color_;
	}

	inline void light::set_attenuation_constant(const double &f) {
		attenuation_constant = f;
		attenuation_enabled = true;
	}

	inline void light::set_attenuation_linear(const double &f) {
		attenuation_linear = f;
		attenuation_enabled = true;
	}

	inline void light::set_attenuation_quadratic(const double &f) {
		attenuation_quadratic = f;
		attenuation_enabled = true;
	}
}

#endif