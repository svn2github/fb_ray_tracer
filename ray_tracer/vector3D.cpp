
#include "vector3D.hpp"

namespace ray_tracer {

	vector3D::vector3D() { 
		x = 0;
		y = 0;
		z = 0;
	}

	vector3D::vector3D(double x_, double y_, double z_) {
		x = x_;
		y = y_;
		z = z_; 
	}
}
