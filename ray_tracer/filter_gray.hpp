#ifndef __FILTER_GRAY_HPP
#define __FILTER_GRAY_HPP

#include "filter.hpp"

namespace ray_tracer {
	class filter_gray : public filter { 
	public:
		filter_gray(filter *);
		void apply_filter(int *, int, int);
	};
}

#endif