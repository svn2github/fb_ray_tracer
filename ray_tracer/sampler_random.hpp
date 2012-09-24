#ifndef __SAMPLER_RANDOM_HPP
#define __SAMPLER_RANDOM_HPP

#include "sampler.hpp"

namespace ray_tracer {
	class sampler_random : public sampler {
	public:
		sampler_random(int);
	protected:
		void generate(int);
	};
}

#endif