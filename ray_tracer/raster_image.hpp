#ifndef __RASTER_IMAGE_HPP
#define __RASTER_IMAGE_HPP

#include "camera.hpp"

namespace ray_tracer {

	class raster_image {
	public:
		friend class camera;

		raster_image();
		raster_image(double, double, double, double);

	private:
		double l, r, t, b;
	};
}

#endif