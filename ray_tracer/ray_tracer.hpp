#ifndef __RAY_TRACER_HPP
#define __RAY_TRACER_HPP

#include "misc.hpp"

namespace ray_tracer {
	class ray_tracer {
	public:	
		colorRGB ray_color(world *, hit_record *);
	private:
		template <class T> T max(T, T);
		double pow(double, int);
	};

	template <class T> 
	inline T ray_tracer::max(T x, T y) {
		return x > y ? x : y;
	}

	inline double ray_tracer::pow(double base, int power) {
		if (power <= 0) {
			return 1;
		} else {
			double result = 1;

			while (power > 0 && result > ray_eps) {
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