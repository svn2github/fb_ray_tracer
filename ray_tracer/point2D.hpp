#ifndef __POINT2D_HPP
#define __POINT2D_HPP

#include <cmath>
#include "misc.hpp"

namespace ray_tracer {
	class point2D {
	public:
		point2D();
		point2D(double, double);
		double length() const;
		double length_squared() const;
		double inv_length() const;
		friend point2D operator*(const point2D &, double);
		friend point2D operator*(double, const point2D &);
	public:
		double x, y;
	};

	inline double point2D::length() const {
		return sqrt(x * x + y * y);
	}

	inline double point2D::length_squared() const {
		return x * x + y * y;
	}

	inline double point2D::inv_length() const {
		return inv_sqrt(x * x + y * y);
	}

	inline point2D operator*(const point2D &p, double f) {
		return point2D(p.x * f, p.y * f);
	}
	
	inline point2D operator*(double f, const point2D &p) {
		return point2D(p.x * f, p.y * f);
	}
}

#endif