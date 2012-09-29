#ifndef __ALGEBRA_QUADRATIC_HPP__
#define __ALGEBRA_QUADRATIC_HPP__

#include "point3D.hpp"
#include "vector3D.hpp"

namespace ray_tracer {
	class algebra_quadratic {
	private:
		template<typename T> 
		void swap(T &a, T &b) const {
			T c = a;
			a = b;
			b = c;
		}
	public:
		double xx, yy, zz, xy, xz, yz, x, y, z, c;
	public:
		algebra_quadratic() {
			xx = 0;
			yy = 0;
			zz = 0;
			xy = 0;
			xz = 0;
			yz = 0;
			x = 0;
			y = 0;
			c = 0;
		}

		double gradient_x(const point3D &p) const {
			return 2 * xx * p.x + xy * p.y + xz * p.z + x;
		}

		double gradient_y(const point3D &p) const {
			return 2 * yy * p.y + xy * p.x + yz * p.z + y;
		}
		
		double gradient_z(const point3D &p) const {
			return 2 * yy * p.z + xz * p.y + yz * p.x + z;
		}

		/* it should be granted that the vector is an unit vector. */
		double find_root(point3D p, vector3D v) const {
			double _xx = 0, _x = 0, _c = 0;
			double _y, _yc, _z, _zc, delta, value1, value2;

			// make sure v.x is not zero
			if (v.x == 0 && v.y != 0) {
				swap(p.x, p.y);
				swap(v.x, v.y);
			} else if (v.x == 0 && v.z != 0) {
				swap(p.x, p.z);
				swap(v.x, v.z);
			}
			// transform y and z to x
			_y = v.y / v.x;
			_yc = p.y - _y * p.x;
			_z = v.z / v.x;
			_zc = p.z - _z * p.x;
			// calcuate the coefficient of quadratic equation
			// xx
			_xx += xx;
			_x += x;
			_c += c;
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
			// find the root
			delta = _x * _x - 4 * _xx * _c;
			if (delta > 0) {
				delta = sqrt(delta);
				value1 = (-_x - delta) / _xx / 2;
				value2 = (-_x + delta) / _xx / 2;
				value1 = (value1 - p.x) / v.x;
				value2 = (value2 - p.x) / v.x;
				if (value1 > value2) {
					swap(value1, value2);
				}
				return value1 < 0 ? value2 : value1;
			}
			return -1;
		}
	};
}

#endif