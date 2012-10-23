
#include "image.hpp"

namespace ray_tracer {

	image::image(void *image_ptr_, int w_, int h_, int bpp_) {
		image_ptr = (uint8_t *)image_ptr_;
		w = w_;
		h = h_;
		bpp = bpp_ / 8;
	}

	colorRGB image::get_color(int x, int y) const {
		uint8_t *ptr = image_ptr + (y * w + x) * bpp;
		// return colorRGB(*(int *)ptr);
		return color_black; // Not implemented
	}
}
	