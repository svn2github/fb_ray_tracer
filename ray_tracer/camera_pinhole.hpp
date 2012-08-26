#ifndef __CAMERA_PINHOLE_HPP
#define __CAMERA_PINHOLE_HPP

#include "camera.hpp"

namespace ray_tracer {
	class camera_pinhole : public camera {
	public:
		camera_pinhole();
		camera_pinhole(const point3D &, const point3D &, const vector3D &);
		ray get_ray(int, int, int, int, raster_image *) const;
		void zoom(double);
	};
}

#endif