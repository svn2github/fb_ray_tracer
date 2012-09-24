
#include "sampler_single.hpp"
#include "misc.hpp"

namespace ray_tracer {

	sampler_single::sampler_single(int num) : sampler(num) { 
		generate(num);
	}

	void sampler_single::generate(int num) {
		samples.push_back(point2D(0, 0));
	}
}