#ifndef __LIGHT_POINT_HPP
#define __LIGHT_POINT_HPP

#include "light.hpp"

namespace ray_tracer {
	class light_point : public light {
	public:
		light_point();
		light_point(const point3D &, const colorRGB &, bool);
	};
}

#endif