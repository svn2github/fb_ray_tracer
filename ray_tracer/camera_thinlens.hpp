#ifndef __CAMERA_THINLENS_HPP
#define __CAMERA_THINLENS_HPP

#include "camera.hpp"
#include "point3D.hpp"
#include "vector3D.hpp"
#include "colorRGB.hpp"
#include "sampler.hpp"

namespace ray_tracer {
	class camera_thinlens : public camera {
	public:
		camera_thinlens();
		camera_thinlens(const point3D &, const point3D &, const vector3D &, double, double, double);
		~camera_thinlens();
		colorRGB render_scene(int, int, int, int, world *) const;
	private:
		void init_sampler(int);
	private:
		double focal_dist, lens_radius;
		sampler *smpler;
	};
}

#endif