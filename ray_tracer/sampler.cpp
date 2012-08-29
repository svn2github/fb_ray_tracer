
#include "sampler.hpp"
#include "misc.hpp"
#include <cmath>
#include <algorithm>

namespace ray_tracer {

	// Origin: Shirley and Chiu(1997)
	void sampler::map_sample_to_disk() {
		for (int i = 0; i < number_samples; i += 1) {
			double x = (samples[i].x - 0.5) * 2, y = (samples[i].y - 0.5) * 2, r, angle;
			if (x > -y) {
				if (x > y) {
					r = x;
					angle = y / x;
				} else {
					r = y;
					angle = 2 - x / y;
				}
			} else {
				if (x < y) {
					r = -x;
					angle = 4 + y / x;
				} else {
					r = -y;
					angle = 6 - x / y;
				}
			}
			angle = angle * pi / 4;
			r /= 2;
			samples[i].x = r * cos(angle) + 0.5;
			samples[i].y = r * sin(angle) + 0.5;
		}
		std::random_shuffle(samples.begin(), samples.end());
	}
};
