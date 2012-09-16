
#include "filter_invert.hpp"
#include "colorRGB.hpp"

namespace ray_tracer {

	filter_invert::filter_invert(filter *next_filter_) : filter(next_filter_) { }

	void filter_invert::apply_filter(int *buf_ptr, int w, int h) {
		int *temp_ptr = buf_ptr;

		for (int y = 0; y < h; y += 1) {
			for (int x = 0; x < w; x += 1) {
				*temp_ptr ++ = (color_white - colorRGB(*temp_ptr)).clamp_to_int();
			}
		}
		filter::apply_filter(buf_ptr, w, h);
	}
}
