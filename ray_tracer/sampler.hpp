#ifndef __SAMPLER_HPP
#define __SAMPLER_HPP

#include "point2D.hpp"
#include <vector>

namespace ray_tracer {
	class sampler {
	public:
		/** All sample's coordinate should be ranged in [0, 1) */
		virtual void generate(int) = 0;
		void map_sample_to_disk();
		point2D get_sampler_unit();
		point2D get_sampler_zoomed(double);
	protected:
		int number_samples;
		int sample_index;
		std::vector<point2D> samples;
	};

	inline point2D sampler::get_sampler_unit() {
		if (++sample_index >= number_samples) sample_index = 0;
		return samples[sample_index];
	}

	inline point2D sampler::get_sampler_zoomed(double zoom) {
		return get_sampler_unit() * zoom;
	}
}

#endif