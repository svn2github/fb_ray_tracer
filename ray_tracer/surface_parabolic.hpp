#ifndef __SURFACE_PARABOLIC_HPP__
#define __SURFACE_PARABOLIC_HPP__

#include "surface.hpp"
#include "algebra_quadratic.hpp"

namespace ray_tracer {
	class surface_parabolic : public surface {
	public:
		surface_parabolic();
		double hit(const ray &) const;
		vector3D get_normal(const point3D &) const;
	private:
		algebra_quadratic quad;
	};
}

#endif