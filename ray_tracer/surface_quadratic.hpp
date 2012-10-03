#ifndef __SURFACE_PARABOLIC_HPP__
#define __SURFACE_PARABOLIC_HPP__

#include "surface.hpp"
#include "algebra_quadratic.hpp"

namespace ray_tracer {
	class surface_quadratic : public surface, public algebra_quadratic {
	public:
		surface_quadratic();
		double hit(const ray &, const surface **) const;
		vector3D get_normal_vector(const point3D &) const;
	};
}

#endif