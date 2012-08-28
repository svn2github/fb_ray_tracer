#ifndef __SURFACE_TRIANGLE_HPP
#define __SURFACE_TRIANGLE_HPP

#include "surface.hpp"
#include "point3D.hpp"
#include "vector3D.hpp"

namespace ray_tracer {
	class surface_triangle : public surface {
	public:
		surface_triangle();
		surface_triangle(const point3D &, const point3D &, const point3D &);
		point3D get_v0() const;
		void set_v0(const point3D &);
		point3D get_v1() const;
		void set_v1(const point3D &);
		point3D get_v2() const;
		void set_v2(const point3D &);
		bool hit(ray *, double, hit_info *) const;
		vector3D get_normal(const point3D &) const;
	private:
		point3D v0, v1, v2;
		vector3D normal;
	};

	inline point3D surface_triangle::get_v0() const {
		return v0;
	}

	inline void surface_triangle::set_v0(const point3D &v0_) {
		v0 = v0_;
		normal = ((v1 - v0) ^ (v2 - v0)).normalized();
	}

	inline point3D surface_triangle::get_v1() const {
		return v1;
	}

	inline void surface_triangle::set_v1(const point3D &v1_) {
		v1 = v1_;
		normal = ((v1 - v0) ^ (v2 - v0)).normalized();
	}
		
	inline point3D surface_triangle::get_v2() const {
		return v2;
	}

	inline void surface_triangle::set_v2(const point3D &v2_) {
		v2 = v2_;
		normal = ((v1 - v0) ^ (v2 - v0)).normalized();
	}
}

#endif
