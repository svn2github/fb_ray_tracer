#ifndef __RAY_HPP
#define __RAY_HPP

#include "vector3D.hpp"
#include "point3D.hpp"

namespace ray_tracer {
	class ray {
	public:
		ray();
		ray(const point3D &, const vector3D &);
		point3D get_origin() const;
		void set_origin(const point3D &);
		vector3D get_dir() const;
		void set_dir(const vector3D &);
	private:
		point3D origin;
		vector3D dir;
	};

	inline point3D ray::get_origin() const {
		return origin;
	}

	inline void ray::set_origin(const point3D &origin_) {
		origin = origin_;
	}

	inline vector3D ray::get_dir() const {
		return dir;
	}

	inline void ray::set_dir(const vector3D &dir_) {
		dir = dir_;
	}
}

#endif