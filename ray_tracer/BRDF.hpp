#ifndef __BRDF_HPP
#define __BRDF_HPP

#include "colorRGB.hpp"
#include "vector3D.hpp"
#include "hitInfo.hpp"

namespace ray_tracer {
	class BRDF {
	public:
		BRDF();
		/** win & wout should be unit vector */
		virtual colorRGB f(hitInfo *, const vector3D &, const vector3D &) = 0;
		void set_coefficient(const colorRGB &);
	protected:
		colorRGB coefficient;
	};

	inline void BRDF::set_coefficient(const colorRGB &coefficient_) {
		coefficient = coefficient_;
	}
}

#endif