#ifndef __TEXTURE_MAPPING_SPHERE_HPP
#define __TEXTURE_MAPPING_SPHERE_HPP

#include "texture_mapping.hpp"

namespace ray_tracer {
	class texture_mapping_sphere : public texture_mapping {
	public:
		point2D get_coordinate(hitInfo *) const;
	};
}

#endif