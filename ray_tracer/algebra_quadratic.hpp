#ifndef __ALGEBRA_QUADRATIC_HPP__
#define __ALGEBRA_QUADRATIC_HPP__

#include "point3D.hpp"
#include "vector3D.hpp"

namespace ray_tracer {
	class algebra_quadratic {
	private:
		template<typename T> 
		void swap(T &, T &) const;
		bool check_point_in_range(const point3D &) const;
	public:
		algebra_quadratic();
		void set_range_x(double, double);
		void set_range_y(double, double);
		void set_range_z(double, double);
		double gradient_x(const point3D &) const;
		double gradient_y(const point3D &) const;
		double gradient_z(const point3D &) const;
		double find_root(const point3D &, const vector3D &) const;
	private:
		double xmin, xmax, ymin, ymax, zmin, zmax;
	public:
		double xx, yy, zz, xy, xz, yz, x, y, z, c;
	};
}

#endif