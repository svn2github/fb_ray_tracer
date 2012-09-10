#ifndef __BRDF_BLINN_PHONG_HPP
#define __BRDF_BLINN_PHONG_HPP

#include "BRDF.hpp"

namespace ray_tracer {
	class BRDF_blinn_phong : public BRDF {
	public:
		colorRGB f(hit_info *, const vector3D &, const vector3D &);
		void set_shininess(const int &);	
	private:
		double pow(double, int);
	private:
		int shininess;
	};

	inline double BRDF_blinn_phong::pow(double base, int power) {
		if (power <= 0) {
			return 1;
		} else {
			double result = 1;

			while (power > 0 && result > epsilon) {
				if (power & 1) {
					result *= base;
				}
				power >>= 1;
				base *= base;
			}
			return result;
		}
	}

	inline void BRDF_blinn_phong::set_shininess(const int &shininess_) {
		shininess = shininess_;
	}
}

#endif