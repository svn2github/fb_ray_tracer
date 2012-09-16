#ifndef __CAMERA_HPP
#define __CAMERA_HPP

#include "vector3D.hpp"
#include "point3D.hpp"
#include "colorRGB.hpp"

namespace ray_tracer {
	class world;
	class camera {
	public:
		camera();
		camera(const point3D &, const point3D &, const vector3D &);
		virtual ~camera() = 0;
		virtual colorRGB render_scene(double, double, int, int, world *) const = 0;
		point3D get_eye() const;
		void set_eye(const point3D &);
		point3D get_lookat() const;
		void set_lookat(const point3D &);
		vector3D get_up() const;
		void set_up(const vector3D &);
		void rotate(double);
	protected:
		void compute_axis();
	protected:
		point3D eye, lookat;
		vector3D up;
		vector3D axis_u, axis_v, axis_w;
	};

	inline point3D camera::get_eye() const {
		return eye;
	}

	inline void camera::set_eye(const point3D &eye_) {
		eye = eye_;
		compute_axis();
	}

	inline point3D camera::get_lookat() const {
		return lookat;
	}

	inline void camera::set_lookat(const point3D &lookat_) {
		lookat = lookat_;
		compute_axis();
	}

	inline vector3D camera::get_up() const {
		return up;
	}

	inline void camera::set_up(const vector3D &up_) {
		up = up_;
		compute_axis();
	}
}

#endif