
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

	double vector3D::length() const {
		return sqrt(x * x + y * y + z * z);
	}

	// This code is copyed from Quake III Q_rsqrt
	double vector3D::inv_length() const {
		float number = (float)(x * x + y * y + z * z);
		int i;
		float x2, yy;
		const float threehalfs = 1.5f;

		x2 = number * 0.5f;
		yy = number;
		i = * (int *) &yy;  // evil floating point bit level hacking
		i = 0x5f3759df - (i >> 1); // what the fuck?
		yy = * (float *) &i;
		yy = yy * (threehalfs - (x2 * yy * yy)); // 1st iteration
		// yy = yy * (threehalfs - (x2 * yy * yy)); // 2nd iteration, this can be removed
		return yy;
	}

	vector3D vector3D::normalized() const {
		double l = inv_length();
		return vector3D(x * l, y * l, z * l);
	}
}
