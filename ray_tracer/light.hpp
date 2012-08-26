#ifndef __LIGHT_HPP
#define __LIGHT_HPP

#include "point3D.hpp"
#include "colorRGB.hpp"

namespace ray_tracer {
	class light {
	public:
		light();
		light(const point3D &, const colorRGB &);
	public:
		point3D position;
		colorRGB color;
	};
}

#endif