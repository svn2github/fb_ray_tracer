#ifndef __SAMPLER_SINGLE_HPP
#define __SAMPLER_SINGLE_HPP

#include "sampler.hpp"

namespace ray_tracer {
	class sampler_single : public sampler {
	public:
		sampler_single(int);
	protected:
		void generate(int);
	};
}

#endif