#ifndef __MISC_HPP
#define __MISC_HPP

#include <cstdlib>

namespace ray_tracer {

	const double pi = 3.1415926535898;
	const double epsilon = 1e-7;
	const double huge_double = 10e10;
	#define dblcmp(_x_) ((_x_) < -epsilon ? -1 : ((_x_) > (epsilon ? 1 : 0)))
	
	// This code is copyed from Quake III Q_rsqrt
	inline float inv_sqrt(float number) {
		int i;
		float x2, yy;
		const float threehalfs = 1.5f;

		x2 = number * 0.5f;
		yy = number;
		i = * (int *) &yy;  // evil floating point bit level hacking
		i = 0x5f3759df - (i >> 1); // what the fuck?
		yy = * (float *) &i;
		yy = yy * (threehalfs - (x2 * yy * yy)); // 1st iteration
		// yy = yy * (threehalfs - (x2 * yy * yy)); // 2nd iteration, this can be removed
		return yy;
	}

	inline void set_seed(int seed) {
		srand(seed);
	}

	inline int random_int() {
		return rand();
	}

	inline double random_double() {
		return (double)rand() / RAND_MAX;
	}
}

#endif