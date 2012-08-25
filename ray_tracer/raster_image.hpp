#ifndef __RASTER_IMAGE_HPP
#define __RASTER_IMAGE_HPP

#include "camera.hpp"
#include "ray.hpp"

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