#ifndef __SAMPLER_JITTERED_HPP
#define __SAMPLER_JITTERED_HPP

#include "sampler.hpp"

namespace ray_tracer {
	class sampler_jittered : public sampler {
	public:
		void generate(int);
	private:
		bool is_squared(int, int &);
	};
}

#endif