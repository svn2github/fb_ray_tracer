#ifndef __IMAGE_MAPPING_HPP
#define __IMAGE_MAPPING_HPP

#include "point2D.hpp"
#include "hitInfo.hpp"

namespace ray_tracer {
	class image_mapping {
	public:
		virtual ~image_mapping() = 0;
		virtual point2D get_coordinate(hitInfo *) const = 0;
	};
}

#endif