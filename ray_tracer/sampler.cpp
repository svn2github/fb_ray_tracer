
#include "sampler.hpp"
#include "misc.hpp"
#include <cmath>

namespace ray_tracer {
	
	sampler::sampler(int num) {
		for (int i = 0; i < sampler_set_count; i += 1) {
			sample_index[i] = i % num;
		}
		mapped_to_disk = false;
		number_samples = num;
		samples.reserve(number_samples);
	}

	sampler::~sampler() { }

	// Origin: Shirley and Chiu(1997)
	void sampler::map_sample_to_disk() {
		if (!mapped_to_disk) {
			mapped_to_disk = true;
			samples_disk.reserve(number_samples);
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
				samples_disk[i].x = r * cos(angle) + 0.5;
				samples_disk[i].y = r * sin(angle) + 0.5;
			}
		}
	}

	void sampler::next_sampler() {
		for (int i = 0; i < sampler_set_count; i += 1) {
			if (++sample_index[i] >= number_samples) sample_index[i] = 0;
		}
	}

	point2D sampler::get_sampler_unit(int set) {
		return samples[sample_index[set]];
	}

	point2D sampler::get_sampler_zoomed(int set, double zoom) {
		return get_sampler_unit(set) * zoom;
	}

	point2D sampler::get_sampler_disk_unit(int set) {
		if (!mapped_to_disk) {
			map_sample_to_disk();
		}
		return samples_disk[sample_index[set]];
	}

	point2D sampler::get_sampler_disk_zoomed(int set, double zoom) {
		return get_sampler_disk_unit(set) * zoom;
	}
};
