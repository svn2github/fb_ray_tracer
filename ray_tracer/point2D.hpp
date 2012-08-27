#ifndef __POINT2D_HPP
#define __POINT2D_HPP

namespace ray_tracer {
	class point2D {
	public:
		point2D();
		point2D(double, double);
		friend point2D operator*(const point2D &, double);
		friend point2D operator*(double, const point2D &);
	public:
		double x, y;
	};

	inline point2D operator*(const point2D &p, double f) {
		return point2D(p.x * f, p.y * f);
	}
	
	inline point2D operator*(double f, const point2D &p) {
		return point2D(p.x * f, p.y * f);
	}
}

#endif