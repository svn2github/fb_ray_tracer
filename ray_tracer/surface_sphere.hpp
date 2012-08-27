#ifndef __SURFACE_SPHERE_HPP
#define __SURFACE_SPHERE_HPP

#include "surface.hpp"

namespace ray_tracer {
	class surface_sphere : public surface {
	public:
		surface_sphere();
		surface_sphere(const point3D &, double);
		point3D get_center() const;
		void set_center(const point3D &);
		double get_radius() const;
		void set_radius(const double &);
		bool hit(ray *, double, hit_info *) const;
		vector3D get_normal(const point3D &) const;
	private:
		point3D center;
		double radius, radius2;
	};

	inline point3D surface_sphere::get_center() const {
		return center;
	}

	inline void surface_sphere::set_center(const point3D &center_) {
		center = center_;
	}

	inline double surface_sphere::get_radius() const {
		return radius;
	}

	inline void surface_sphere::set_radius(const double &radius_) {
		radius = radius_;
		radius2 = radius_ * radius_;
	}
}

#endif
