#ifndef __SURFACE_DISK_HPP
#define __SURFACE_DISK_HPP

#include "surface.hpp"

namespace ray_tracer {
	class surface_disk : public surface {
	public:
		surface_disk();
		surface_disk(const point3D &, const vector3D &, double);
		point3D get_center() const;
		void set_center(const point3D &);
		double get_radius() const;
		void set_radius(const double &);
		vector3D get_normal() const;
		void set_normal(const vector3D &);
		bool hit(ray *, double, hitInfo *) const;
		vector3D get_normal(const point3D &) const;
	private:
		point3D center;
		vector3D normal;
		double radius, radius_squared;
	};

	inline point3D surface_disk::get_center() const {
		return center;
	}
	
	inline void surface_disk::set_center(const point3D &center_) {
		center = center_;
	}

	inline vector3D surface_disk::get_normal() const {
		return normal;
	}

	inline void surface_disk::set_normal(const vector3D &normal_) {
		normal = normal_.normalized();
	}
	
	inline double surface_disk::get_radius() const {
		return radius;
	}

	inline void surface_disk::set_radius(const double &radius_) {
		radius = radius_;
		radius_squared = radius_ * radius_;
	}
}

#endif