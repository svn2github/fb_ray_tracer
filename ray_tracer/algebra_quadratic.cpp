
#include "algebra_quadratic.hpp"

namespace ray_tracer {
	algebra_quadratic::algebra_quadratic() {
		xx = yy = zz = xy = xz = yz = x = y = c = 0;
		xmin = ymin = zmin = -huge_double;
		xmax = ymax = zmax = huge_double;
	}

	template<typename T> 
	void algebra_quadratic::swap(T &a, T &b) const {
		T c = a;
		a = b;
		b = c;
	}

	bool algebra_quadratic::check_point_in_range(const point3D &p) const {
		if (p.x < xmin || p.x > xmax) {
			return false;
		}
		if (p.y < ymin || p.y > ymax) {
			return false;
		}
		if (p.z < zmin || p.z > zmax) {
			return false;
		}
		return true;
	}

	void algebra_quadratic::set_range_x(double xmin_, double xmax_) {
		xmin = xmin_;
		xmax = xmax_;
	}

	void algebra_quadratic::set_range_y(double ymin_, double ymax_) {
		ymin = ymin_;
		ymax = ymax_;
	}

	void algebra_quadratic::set_range_z(double zmin_, double zmax_) {
		zmin = zmin_;
		zmax = zmax_;
	}

	double algebra_quadratic::gradient_x(const point3D &p) const {
		return 2 * xx * p.x + xy * p.y + xz * p.z + x;
	}

	double algebra_quadratic::gradient_y(const point3D &p) const {
		return 2 * yy * p.y + xy * p.x + yz * p.z + y;
	}

	double algebra_quadratic::gradient_z(const point3D &p) const {
		return 2 * zz * p.z + xz * p.x + yz * p.y + z;
	}

	/* it should be granted that the vector is an unit vector. */
	double algebra_quadratic::find_root(const point3D &p_, const vector3D &v_) const {
		point3D p = p_;
		vector3D v = v_;
		double _xx = 0, _x = 0, _c = 0;
		double _y, _yc, _z, _zc, delta, value1, value2;
		bool valid1, valid2;

		// make sure v.x is not zero.
		if (v.x == 0 && v.y != 0) {
			swap(p.x, p.y);
			swap(v.x, v.y);
		} else if (v.x == 0 && v.z != 0) {
			swap(p.x, p.z);
			swap(v.x, v.z);
		}
		// transform y and z to x.
		_y = v.y / v.x;
		_yc = p.y - _y * p.x;
		_z = v.z / v.x;
		_zc = p.z - _z * p.x;
		// calcuate the coefficient of quadratic equation.
		// xx
		_xx += xx;
		_x += 0;
		_c += 0;
		// yy
		_xx += yy * _y * _y;
		_x += yy * 2 * _y * _yc;
		_c += yy * _yc * _yc;
		// zz
		_xx += zz * _z * _z;
		_x += zz * 2 * _z * _zc;
		_c += zz * _zc * _zc;
		// xy
		_xx += xy * _y;
		_x += xy * _yc;
		_c += 0;
		// xz
		_xx += xz * _z;
		_x += xz * _zc;
		_c += 0;
		// yz
		_xx += yz * _y * _z;
		_x += yz * (_y * _zc + _z * _yc);
		_c += yz * _yc * _zc;
		// x
		_xx += 0;
		_x += x;
		_c += 0;
		// y
		_xx += 0;
		_x += y * _y;
		_c += y * _yc;
		// z
		_xx += 0;
		_x += z * _z;
		_c += z * _zc;
		// c
		_xx += 0;
		_x += 0;
		_c += c;
		// find the root.
		delta = _x * _x - 4 * _xx * _c;
		if (delta >= 0) {
			delta = sqrt(delta);
			value1 = ((-_x - delta) / _xx / 2 - p.x) / v.x;
			value2 = ((-_x + delta) / _xx / 2 - p.x) / v.x;
			if (value1 > value2) {
				swap(value1, value2);
			}
			/* epsilon: avoid hit itself. */
			valid1 = (value1 > epsilon) && check_point_in_range(p_ + v_ * value1);
			valid2 = (value2 > epsilon) && check_point_in_range(p_ + v_ * value2);
			if (valid1) {
				return value1;
			} else if (valid2) {
				return value2;
			} else {
				return -1;
			}
		}
		return -1;
	}
}
