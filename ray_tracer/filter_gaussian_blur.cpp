
#include "filter_gaussian_blur.hpp"
#include "misc.hpp"
#include <cmath>
#include "colorRGB.hpp"
#include <cstring>

namespace ray_tracer {

	filter_gaussian_blur::filter_gaussian_blur(double sigma_, int radius_, filter *next_filter_) {
		next_filter = next_filter_;
		sigma = sigma_;
		radius = radius_;
		guassian_template = new double[(2 * radius_ + 1) * (2 * radius_ + 1)];

		double *template_ptr = guassian_template;
		double deno1_inv = 0;
		double deno2_inv = -1.0 / (2.0 * sigma * sigma);

		for (int i = -radius; i <= radius; i += 1) {
			for (int j = -radius; j <= radius; j += 1) {
				*template_ptr = exp((i * i + j * j) * deno2_inv);
				deno1_inv += *template_ptr ++;
			}
		}
		template_ptr = guassian_template;
		deno1_inv = 1 / deno1_inv;
		for (int i = -radius; i <= radius; i += 1) {
			for (int j = -radius; j <= radius; j += 1) {
				*template_ptr = (*template_ptr) * deno1_inv;
				template_ptr ++;
			}
		}
	}

	filter_gaussian_blur::~filter_gaussian_blur() {
		delete[] guassian_template;
	}

	void filter_gaussian_blur::apply_filter(int *buf_ptr, int w, int h) {
		double *template_ptr;
		colorRGB color;
		int *temp_buf_ptr = new int[w * h];

		memcpy(temp_buf_ptr, buf_ptr, w * h * sizeof(int));
		for (int y = 0; y < h; y += 1) {
			for (int x = 0; x < w; x += 1) {
				color = color_black;
				template_ptr = guassian_template;
				for (int yy = -radius; yy <= radius; yy += 1) {
					if (y + yy >= 0 && y + yy < h) {
						for (int xx = -radius; xx <= radius; xx += 1) {
							if (x + xx >= 0 && x + xx < w) {
								color += colorRGB(*(temp_buf_ptr + (y + yy) * w + (x + xx))) * (*template_ptr);
							} else {
								template_ptr += 1;
							}
						}
					} else {
						template_ptr += (2 * radius + 1);
					}
				}
				*(buf_ptr + y * w + x) = color.clamp_to_int();
			}
		}
		delete[] temp_buf_ptr;
		filter::apply_filter(buf_ptr, w, h);
	}
}