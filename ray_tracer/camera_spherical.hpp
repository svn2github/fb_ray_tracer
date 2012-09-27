#ifndef __CAMERA_SPHERICAL_HPP__
#define __CAMERA_SPHERICAL_HPP__

#include "camera.hpp"
#include "point3D.hpp"
#include "vector3D.hpp"
#include "colorRGB.hpp"

namespace ray_tracer {
	class camera_spherical : public camera {
	public:
		camera_spherical();
		camera_spherical(const point3D &, const point3D &, const vector3D &, double, double);
		colorRGB render_scene(double, double, int, int, hitInfo *) const;
	private:
		double fov_u, fov_v;
	};
}

#endif