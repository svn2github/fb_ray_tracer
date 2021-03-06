#ifndef __BRDF_HPP__
#define __BRDF_HPP__

#include "colorRGB.hpp"
#include "vector3D.hpp"
#include "hitInfo.hpp"

namespace ray_tracer {
	class BRDF {
	public:
		BRDF(const colorRGB &);
		/** win & wout should be unit vector */
		virtual colorRGB f(hitInfo *, const vector3D &, const vector3D &) const;
		virtual colorRGB reflect_f(hitInfo *, const vector3D &) const;
	protected:
		colorRGB rho;
	};
}

#endif