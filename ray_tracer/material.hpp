#ifndef __MATERIAL_HPP
#define __MATERIAL_HPP

#include "colorRGB.hpp"

namespace ray_tracer {
	class material {
	public:
		// virtual ~material() = 0;
	public:
		int shininess;
		colorRGB diffuse, specular, ambient;
	};
}

#endif