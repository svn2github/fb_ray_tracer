
#include "raster_image.hpp"

namespace ray_tracer {

	raster_image::raster_image() {
		l = 0;
		r = 0;
		t = 0;
		b = 0;
	}

	raster_image::raster_image(double l_, double r_, double t_, double b_) {
		l = l_;
		r = r_;
		t = t_;
		b = b_;
	}
}