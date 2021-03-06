#ifndef __CAMERA_THINLENS_HPP__
#define __CAMERA_THINLENS_HPP__

#include "camera.hpp"
#include "point3D.hpp"
#include "vector3D.hpp"
#include "colorRGB.hpp"

namespace ray_tracer {
	class camera_thinlens : public camera {
	public:
		camera_thinlens();
		camera_thinlens(const point3D &, const point3D &, const vector3D &, double, double, double, double, bool);
		colorRGB render_scene(double, double, int, int, hitInfo *) const;
	private:
		double focal_dist, lens_radius;
		double fov_u, fov_v, tan_fov_u_coef, tan_fov_v_coef;
		bool spherical;
	};
}

#endif