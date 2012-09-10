#ifndef __SURFACE_PLANE_HPP
#define __SURFACE_PLANE_HPP

#include "surface.hpp"

namespace ray_tracer {
	class surface_plane : public surface {
	public:
		surface_plane();
		surface_plane(const point3D &, const vector3D &);
		point3D get_point_on_plane() const;
		void set_point_on_plane(const point3D &);
		vector3D get_normal() const;
		void set_normal(const vector3D &);
		bool hit(ray *, double, hit_info *) const;
		vector3D get_normal(const point3D &) const;
	protected:
		point3D point_on_plane;
		vector3D normal;
	};

	inline point3D surface_plane::get_point_on_plane() const {
		return point_on_plane;
	}
	
	inline void surface_plane::set_point_on_plane(const point3D &point_on_plane_) {
		point_on_plane = point_on_plane_;
	}

	inline vector3D surface_plane::get_normal() const {
		return normal;
	}

	inline void surface_plane::set_normal(const vector3D &normal_) {
		normal = normal_.normalized();
	}

	class surface_plane_bw : public surface_plane {
	public:
		surface_plane_bw();
		surface_plane_bw(const point3D &, const vector3D &);
		void get_color(const point3D &, colorRGB *) const;
	};
}

#endif