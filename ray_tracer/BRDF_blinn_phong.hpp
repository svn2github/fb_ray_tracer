#ifndef __BRDF_BLINN_PHONG_HPP
#define __BRDF_BLINN_PHONG_HPP

#include "BRDF.hpp"

namespace ray_tracer {
	class BRDF_blinn_phong : public BRDF {
	public:
		colorRGB f(hitInfo *, const vector3D &, const vector3D &);
		void set_shininess(const int &);	
	private:
		int shininess;
	};

	inline void BRDF_blinn_phong::set_shininess(const int &shininess_) {
		shininess = shininess_;
	}
}

#endif