#ifndef __IMAGE_HPP
#define __IMAGE_HPP

#include "colorRGB.hpp"
#include <cstdint>

namespace ray_tracer {
	class image {
	public:
		image(void *, int, int, int);
		colorRGB get_color(int, int) const;
		int get_w() const;
		int get_h() const;
	private:
		int w, h, bpp;
		uint8_t *image_ptr;
	};

	inline int image::get_w() const {
		return w;
	}

	inline int image::get_h() const {
		return h;
	}
}

#endif