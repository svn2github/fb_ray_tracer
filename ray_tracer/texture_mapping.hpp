#ifndef __TEXTURE_MAPPING_HPP
#define __TEXTURE_MAPPING_HPP

#include "point2D.hpp"
#include "hitInfo.hpp"

namespace ray_tracer {
	class texture_mapping {
	public:
		virtual ~texture_mapping() = 0;
		virtual point2D get_coordinate(hitInfo *) const = 0;
	};
}

#endif