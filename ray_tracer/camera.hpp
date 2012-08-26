#ifndef __CAMERA_HPP
#define __CAMERA_HPP

#include "vector3D.hpp"
#include "point3D.hpp"
#include "ray.hpp"

namespace ray_tracer {
	class camera {
		friend class raster_image;
	public:
		camera();
		camera(const point3D &, const vector3D &, const vector3D &);
		ray camera::get_ray(int, int, int, int, raster_image *);
	protected:
		point3D position;
		vector3D axis_u, axis_v, axis_w;
	};
}

#endif