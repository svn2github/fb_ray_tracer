#ifndef __FOG_HPP__
#define __FOG_HPP__

#include "colorRGB.hpp"
#include "hitInfo.hpp"

namespace ray_tracer {
	class fog {
		friend class world;
	public:
		fog();
		fog(double, int, const colorRGB &);
		colorRGB fog_blending(hitInfo *, const point3D &, const colorRGB &) const;
	private:
		int exponent;
		double density;
		colorRGB fog_color;
	};
}

#endif