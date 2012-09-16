#ifndef __LIGHT_SPOT_HPP
#define __LIGHT_SPOT_HPP

#include "light.hpp"

namespace ray_tracer {
	class light_spot : public light {
	public:
		light_spot();
		light_spot(const point3D &, const colorRGB &, const vector3D &, double, int);
		colorRGB light_shade(hitInfo *) const;
		bool in_range(hitInfo *) const;
		void set_direcion(const vector3D &);
		/** cutoff is ranged in [0, pi / 2] */
		void set_cutoff(const double &);
		void set_exponent(const int &);
	private:
		vector3D direction;
		double cutoff, cos_cutoff;
		int exponent;
	};

	inline void light_spot::set_direcion(const vector3D &direction_) {
		direction = direction_.normalized();
	}

	inline void light_spot::set_cutoff(const double &cutoff_) {
		cutoff = cutoff_;
		cos_cutoff = cos(cutoff);
	}

	inline void light_spot::set_exponent(const int &exponent_) {
		exponent = exponent_;
	}
}

#endif