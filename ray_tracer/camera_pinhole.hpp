#ifndef __CAMERA_PINHOLE_HPP__
#define __CAMERA_PINHOLE_HPP__

#include "camera.hpp"
#include "point3D.hpp"
#include "vector3D.hpp"
#include "colorRGB.hpp"

namespace ray_tracer {
	class camera_pinhole : public camera {
	public:
		camera_pinhole();
		camera_pinhole(const point3D &, const point3D &, const vector3D &, double);
		colorRGB render_scene(double, double, int, int, hitInfo *) const;
		void zoom(double);
	private:
		double view_dist;
	};
}

#endif