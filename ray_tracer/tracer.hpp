#ifndef __TRACER_HPP
#define __TRACER_HPP

#include "misc.hpp"
#include "colorRGB.hpp"
#include "hitInfo.hpp"

namespace ray_tracer {
	class world;
	class tracer {
	public:	
		colorRGB ray_color(hitInfo *);
	};
}

#endif