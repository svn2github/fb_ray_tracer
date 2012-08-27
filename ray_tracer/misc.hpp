#ifndef __MISC_HPP
#define __MISC_HPP

#include <cstdlib>

namespace ray_tracer {

	const double pi = 3.1415926535898;
	const double epsilon = 1e-7;
	const double huge_double = 10e10;
	#define dblcmp(_x_) ((_x_) < -epsilon ? -1 : ((_x_) > (epsilon ? 1 : 0)))

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