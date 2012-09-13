#ifndef __POINT3D_HPP
#define __POINT3D_HPP

#include "vector3D.hpp"

namespace ray_tracer {
	class vector3D;
	class point3D {
	public:
		point3D();
		point3D(double, double, double);
		vector3D to_vector() const;
		friend point3D operator+(const point3D &, const vector3D &);
		friend point3D &operator+=(point3D &, const vector3D &);
		friend vector3D operator-(const point3D &, const point3D &);
		friend point3D operator-(const point3D &, const vector3D &);
	public:
		double x, y, z;
	};

	inline point3D operator+(const point3D &p, const vector3D &v) {
		return point3D(p.x + v.x, p.y + v.y, p.z + v.z);
	}

	inline point3D &operator+=(point3D &p, const vector3D &v) {
		p.x += v.x;
		p.y += v.y;
		p.z += v.z;
		return p;
	}

	inline vector3D operator-(const point3D &p1, const point3D &p2) {
		return vector3D(p1.x - p2.x, p1.y - p2.y, p1.z - p2.z);
	}

	inline point3D operator-(const point3D &p, const vector3D &v) {
		return point3D(p.x - v.x, p.y - v.y, p.z - v.z);
	}
}

#endif