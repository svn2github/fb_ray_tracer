
#include "sampler_random.hpp"
#include "misc.hpp"

namespace ray_tracer {

	void sampler_random::generate(int num) {
		number_samples = num;
		sample_index = 0;
		samples.reserve(number_samples);
		for (int i = 0; i < number_samples; i += 1) {
			samples.push_back(point2D(random_double(), random_double()));
		}
	}
}