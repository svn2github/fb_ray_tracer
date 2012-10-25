
#include "algebra_quadratic.hpp"
#include <algorithm>

namespace ray_tracer {
	algebra_quadratic::algebra_quadratic() {
		coef_xx = coef_yy = coef_zz = coef_xy = coef_xz = coef_yz = coef_x = coef_y = coef_z = coef_const = 0;
		xmin = ymin = zmin = -huge_double;
		xmax = ymax = zmax = huge_double;
	}

	bool algebra_quadratic::check_point_in_range(const point3D &p) const {
		if (p.x < xmin || p.x > xmax) return false;
		if (p.y < ymin || p.y > ymax) return false;
		if (p.z < zmin || p.z > zmax) return false;
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
		return 2 * coef_xx * p.x + coef_xy * p.y + coef_xz * p.z + coef_x;
	}

	double algebra_quadratic::gradient_y(const point3D &p) const {
		return 2 * coef_yy * p.y + coef_xy * p.x + coef_yz * p.z + coef_y;
	}

	double algebra_quadratic::gradient_z(const point3D &p) const {
		return 2 * coef_zz * p.z + coef_xz * p.x + coef_yz * p.y + coef_z;
	}

	/* it should be granted that the vector is an unit vector. */
	double algebra_quadratic::find_root(const point3D &p_, const vector3D &v_) const {
		point3D p = p_;
		vector3D v = v_;
		double quadratic_a = 0, quadratic_b = 0, quadratic_c = 0;
		double ycoef, yconst, zcoef, zconst, delta, value1, value2;
		bool valid1, valid2;

		// make sure v.x is not zero.
		if (v.x == 0 && v.y != 0) {
			std::swap(p.x, p.y);
			std::swap(v.x, v.y);
		} else if (v.x == 0 && v.z != 0) {
			std::swap(p.x, p.z);
			std::swap(v.x, v.z);
		}
		// transform y and z to x.
		ycoef = v.y / v.x;
		yconst = p.y - ycoef * p.x;
		zcoef = v.z / v.x;
		zconst = p.z - zcoef * p.x;
		// calcuate the coefficient of quadratic equation.
		// coefx_x
		quadratic_a += coef_xx;
		quadratic_b += 0;
		quadratic_c += 0;
		// coef_yy
		quadratic_a += coef_yy * ycoef * ycoef;
		quadratic_b += coef_yy * 2 * ycoef * yconst;
		quadratic_c += coef_yy * yconst * yconst;
		// coef_zz
		quadratic_a += coef_zz * zcoef * zcoef;
		quadratic_b += coef_zz * 2 * zcoef * zconst;
		quadratic_c += coef_zz * zconst * zconst;
		// coef_xy
		quadratic_a += coef_xy * ycoef;
		quadratic_b += coef_xy * yconst;
		quadratic_c += 0;
		// coef_xz
		quadratic_a += coef_xz * zcoef;
		quadratic_b += coef_xz * zconst;
		quadratic_c += 0;
		// coef_yz
		quadratic_a += coef_yz * ycoef * zcoef;
		quadratic_b += coef_yz * (ycoef * zconst + zcoef * yconst);
		quadratic_c += coef_yz * yconst * zconst;
		// coef_x
		quadratic_a += 0;
		quadratic_b += coef_x;
		quadratic_c += 0;
		// coef_y
		quadratic_a += 0;
		quadratic_b += coef_y * ycoef;
		quadratic_c += coef_y * yconst;
		// coef_z
		quadratic_a += 0;
		quadratic_b += coef_z * zcoef;
		quadratic_c += coef_z * zconst;
		// c
		quadratic_a += 0;
		quadratic_b += 0;
		quadratic_c += coef_const;
		// find the root.
		delta = quadratic_b * quadratic_b - 4 * quadratic_a * quadratic_c;
		if (delta >= 0) {
			delta = sqrt(delta);
			value1 = ((-quadratic_b - delta) / quadratic_a / 2 - p.x) / v.x;
			value2 = ((-quadratic_b + delta) / quadratic_a / 2 - p.x) / v.x;
			if (value1 > value2) std::swap(value1, value2);
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
