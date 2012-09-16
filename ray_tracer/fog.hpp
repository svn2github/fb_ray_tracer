#ifndef __FOG_HPP
#define __FOG_HPP

#include "colorRGB.hpp"
#include "hitInfo.hpp"

namespace ray_tracer {
	class fog {
	public:
		fog();
		fog(double, int, const colorRGB &);
		colorRGB mix_fog(hitInfo *, const point3D &, const colorRGB &);
		colorRGB get_fog_color() const;
		double get_density() const;
	private:
		int exponent;
		double density;
		colorRGB fog_color;
	};

	inline colorRGB fog::get_fog_color() const {
		return fog_color;
	} 
}

#endif