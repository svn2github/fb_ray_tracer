#ifndef __CAMERA_ORTHOGRAPHIC_HPP
#define __CAMERA_ORTHOGRAPHIC_HPP

#include "camera.hpp"

namespace ray_tracer {
	class camera_orthographic : public camera {
	public:
		camera_orthographic();
		camera_orthographic(const point3D &, const point3D &, const vector3D &);
		ray get_ray(int, int, int, int, raster_image *) const;
	};
}

#endif