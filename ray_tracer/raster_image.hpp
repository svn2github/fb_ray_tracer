#ifndef __RASTER_IMAGE_HPP
#define __RASTER_IMAGE_HPP

#include "vector3D.hpp"
#include "world.hpp"

namespace ray_tracer {

	class raster_image {
	public:
		raster_image();
		raster_image(double, double, double, double);

		ray get_ray(int, int, int, int, camera *);

	private:
		double l, r, t, b;
	};
}

#endif