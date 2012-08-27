
#include "sampler.hpp"
#include "misc.hpp"
#include <cmath>

namespace ray_tracer {
	
	/* 
		TODO:
		This implementation has something wrong
		need to be corrected
	*/
	void sampler::map_sample_to_disk() {
		for (int i = 0; i < number_samples; i += 1) {
			double angle = samples[i].x * 2 * pi, dist = samples[i].y / 2;
			double x = cos(angle) * dist, y = sin(angle) * dist;

			samples[i].x = x + 0.5;
			samples[i].y = y + 0.5;
		}
	}
};
