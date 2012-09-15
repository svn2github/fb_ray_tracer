#ifndef __LIGHT_POINT_HPP
#define __LIGHT_POINT_HPP

#include "light.hpp"
#include "point3D.hpp"
#include "colorRGB.hpp"
#include "hitInfo.hpp"
#include "ray.hpp"

namespace ray_tracer {
	class light_point : public light {
	public:
		light_point();
		light_point(const point3D &, const colorRGB &);
		bool under_shadow(hitInfo *) const;
	};
}

#endif