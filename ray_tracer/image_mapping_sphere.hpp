#ifndef __IMAGE_MAPPING_SPHERE_HPP
#define __IMAGE_MAPPING_SPHERE_HPP

#include "image_mapping.hpp"

namespace ray_tracer {
	class image_mapping_sphere : public image_mapping {
	public:
		point2D get_coordinate(hitInfo *) const;
	};
}

#endif