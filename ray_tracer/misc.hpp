#ifndef __MISC_HPP
#define __MISC_HPP

namespace ray_tracer {

	const double ray_eps = 1e-7;
	const double ray_huge_double = 10e10;
#define ray_dblcmp(_x_) ((_x_) < -ray_eps ? -1 : ((_x_) > (ray_eps ? 1 : 0)))
}

#endif