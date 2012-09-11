#ifndef __TEXTURE_HPP
#define __TEXTURE_HPP

#include "point3D.hpp"
#include "colorRGB.hpp"
#include "hit_info.hpp"

namespace ray_tracer {
	class texture {
	public:
		virtual ~texture() = 0;
		virtual colorRGB texture_shade(hit_info *) = 0;
	};
}

#endif