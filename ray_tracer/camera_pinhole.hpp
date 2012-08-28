#ifndef __CAMERA_PINHOLE_HPP
#define __CAMERA_PINHOLE_HPP

#include "camera.hpp"
#include "point3D.hpp"
#include "vector3D.hpp"
#include "colorRGB.hpp"

namespace ray_tracer {
	class camera_pinhole : public camera {
	public:
		camera_pinhole();
		camera_pinhole(const point3D &, const point3D &, const vector3D &, double);
		colorRGB render_scene(double, double, int, int, world *) const;
		void zoom(double);
	private:
		double view_dist;
	};
}

#endif