#ifndef __TRACER_HPP
#define __TRACER_HPP

#include "misc.hpp"
#include "colorRGB.hpp"
#include "hitInfo.hpp"

namespace ray_tracer {
	class world;
	class tracer {
	public:	
		colorRGB ray_color(hitInfo *);
	private:
		double pow(double, int);
	};

	inline double tracer::pow(double base, int power) {
		if (power <= 0) {
			return 1;
		} else {
			double result = 1;

			while (power > 0 && result > epsilon) {
				if (power & 1) {
					result *= base;
				}
				power >>= 1;
				base *= base;
			}
			return result;
		}
	}
}

#endif