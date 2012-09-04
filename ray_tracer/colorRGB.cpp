
#include "colorRGB.hpp"

namespace ray_tracer {

	colorRGB::colorRGB() {
		r = 0;
		g = 0;
		b = 0;
	}

	colorRGB::colorRGB(double r_, double g_, double b_) {
		r = r_;
		g = g_;
		b = b_;
	}

	colorRGB::colorRGB(int c) {
		b = (double)(c & 255) / 255;
		c >>= 8;
		g = (double)(c & 255) / 255;
		c >>= 8;
		r = (double)(c & 255) / 255;
	}

	colorRGB color_black = colorRGB(0.0, 0.0, 0.0);
	colorRGB color_white = colorRGB(1.0, 1.0, 1.0);
	colorRGB color_red   = colorRGB(1.0, 0.0, 0.0);
	colorRGB color_green = colorRGB(0.0, 1.0, 0.0);
	colorRGB color_blue  = colorRGB(0.0, 0.0, 1.0);
}
