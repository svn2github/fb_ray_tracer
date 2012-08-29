
#include "sampler_jittered.hpp"
#include "misc.hpp"
#include <cmath>
#include <algorithm>

namespace ray_tracer {

	bool sampler_jittered::is_squared(int number, int &root) {
		root = (int)floor(sqrt((double)number) + epsilon);
		return root * root == number;
	}

	void sampler_jittered::generate(int num) {
		int root;
		if (is_squared(num, root)) {
			number_samples = num;
			sample_index = 0;
			samples.reserve(number_samples);
			for (int i = 0; i < root; i += 1) {
				for (int j = 0; j < root; j += 1) {
					samples.push_back(point2D((i + random_double()) / root, (j + random_double()) / root));
				}
			}
			std::random_shuffle(samples.begin(), samples.end());
		} else {
			throw "Sampler_jittered: number of sampler is not squared.";
		}
	}
}