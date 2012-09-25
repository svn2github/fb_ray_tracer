#ifndef __CAMERA_HPP
#define __CAMERA_HPP

#include "vector3D.hpp"
#include "point3D.hpp"
#include "colorRGB.hpp"
#include "hitInfo.hpp"

namespace ray_tracer {
	class world;
	class camera {
	public:
		camera();
		camera(const point3D &, const point3D &, const vector3D &);
		virtual ~camera() = 0;
		virtual colorRGB render_scene(double, double, int, int, hitInfo *) = 0;
		colorRGB render_scene(const point3D &, const vector3D &, hitInfo *);
		point3D get_origin() const;
		void rotate(double);
	protected:
		void compute_axis();
	protected:
		point3D eye, lookat;
		vector3D up;
		vector3D axis_u, axis_v, axis_w;
	};

	inline point3D camera::get_origin() const {
		return eye;
	}
}

#endif