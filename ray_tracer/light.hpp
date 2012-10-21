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
		void set_shadow(bool);
		void set_spot(const vector3D &, double, int);
		void set_attenuation(double, double, double);
		bool under_shadow(hitInfo *) const;
		virtual colorRGB light_shade(hitInfo *) const;
		bool in_range(hitInfo *) const;
		void inherit_light(const light *);
	private:
		void init_attenuation();
	protected:
		point3D position;
		colorRGB color;
	private:
		// Inherits information
		double traveled_dist;
		// Attitudes
		bool cast_shadow, spot_enabled, attenuation_enabled;
		// Spot
		vector3D direction;
		double cutoff, cos_cutoff;
		int exponent;
		// Attenuation
		double attenuation_constant, attenuation_linear, attenuation_quadratic;
	};

	inline void light::set_position(const point3D &position_) {
		position = position_;
	}

	inline void light::set_color(const colorRGB &color_) {
		color = color_;
	}

	inline void light::set_shadow(bool shadow_) {
		cast_shadow = shadow_;
	}

	inline void light::set_spot(const vector3D &direction_, double cutoff_, int exponent_) {
		direction = direction_.normalized();
		cutoff = cutoff_;
		cos_cutoff = cos(cutoff);
		exponent = exponent_;
		spot_enabled = true;
	}

	inline void light::set_attenuation(double constant_, double linear_, double quadratic_) {
		attenuation_constant = constant_;
		attenuation_linear = linear_;
		attenuation_quadratic = quadratic_;
		attenuation_enabled = true;
	}
}

#endif