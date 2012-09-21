
#include "vector3D.hpp"
#include "point3D.hpp"
#include <cassert>

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

	vector3D vector3D::create_vertical() const {
		vector3D v1 = *this;
		vector3D v2, v3;

		if (dblcmp(v1.x) == 0 && dblcmp(v1.y) == 0 && dblcmp(v1.z) == 0) {
			return v1;
		} else {
			while (true) {
				v2.x = random_double() * random_int();
				v2.y = random_double() * random_int();
				v2.z = random_double() * random_int();
				v3 = v1 ^ v2;
				if (dblcmp(v3.length()) != 0) {
					return v3.normalized();
				}
			}
		}
		assert(false);
		return vector3D(); // never be here
	}
}
