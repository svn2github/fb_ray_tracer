#ifndef __LIGHT_HPP__
#define __LIGHT_HPP__

#include "point3D.hpp"
#include "colorRGB.hpp"
#include "hitInfo.hpp"
#include "ray.hpp"

namespace ray_tracer {
	class light {
	public:
		light();
		light(const point3D &, const colorRGB &);
		virtual ~light();
		virtual point3D get_light_origin(hitInfo *) const;
		void set_position(const point3D &);
		void set_color(const colorRGB &);
		void enable_shadow(bool);
		void set_attenuation_constant(double);
		void set_attenuation_linear(double);
		void set_attenuation_quadratic(double);
		bool under_shadow(hitInfo *) const;
		virtual colorRGB light_shade(hitInfo *) const;
		virtual bool in_range(hitInfo *) const;
		void inherit_light(const light *);
	private:
		void init_attenuation();
	protected:
		point3D position;
		colorRGB color;
	private:
		double traveled_dist;
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

	inline void light::enable_shadow(bool shadow_) {
		cast_shadow = shadow_;
	}

	inline void light::set_attenuation_constant(double f) {
		attenuation_constant = f;
		attenuation_enabled = true;
	}

	inline void light::set_attenuation_linear(double f) {
		attenuation_linear = f;
		attenuation_enabled = true;
	}

	inline void light::set_attenuation_quadratic(double f) {
		attenuation_quadratic = f;
		attenuation_enabled = true;
	}
}

#endif