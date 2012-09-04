
#include "filter_gray.hpp"
#include "colorRGB.hpp"

namespace ray_tracer {

	filter_gray::filter_gray(filter *next_filter_) {
		next_filter = next_filter_;
	}

	void filter_gray::apply_filter(int *buf_ptr, int w, int h) {
		colorRGB color;
		int *temp_ptr = buf_ptr;
		double average;

		for (int y = 0; y < h; y += 1) {
			for (int x = 0; x < w; x += 1) {
				color = colorRGB(*temp_ptr);
				average = (color.r + color.g + color.b) / 3;
				color.r = color.g = color.b = average;
				*temp_ptr ++ = color.clamp_to_int();
			}
		}
		filter::apply_filter(buf_ptr, w, h);
	}
}
