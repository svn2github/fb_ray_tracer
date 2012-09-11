#ifndef __TEXTURE_CHECKER_HPP
#define __TEXTURE_CHECKER_HPP

#include "texture.hpp"

namespace ray_tracer {
	class texture_checker : public texture {
	public:
		colorRGB texture_shade(hit_info *);
	};
}

#endif