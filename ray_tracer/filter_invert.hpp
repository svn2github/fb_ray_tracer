#ifndef __FILTER_INVERT_HPP
#define __FILTER_INVERT_HPP

#include "filter.hpp"

namespace ray_tracer {
	class filter_invert : public filter { 
	public:
		filter_invert(filter *);
		void apply_filter(int *, int, int);
	};
}

#endif