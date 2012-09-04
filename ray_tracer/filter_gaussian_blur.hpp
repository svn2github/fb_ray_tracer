#ifndef __FILTER_GAUSSIAN_BLUR_HPP
#define __FILTER_GAUSSIAN_BLUR_HPP

#include "filter.hpp"

namespace ray_tracer {
	class filter_gaussian_blur : public filter { 
	public:
		filter_gaussian_blur(double, int, filter *);
		~filter_gaussian_blur();
		void apply_filter(int *, int, int);
	private:
		double *guassian_template;
		double sigma;
		int radius;
	};
}

#endif