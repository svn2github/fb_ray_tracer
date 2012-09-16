
#include "filter.hpp"

namespace ray_tracer {

	filter::filter() {
		next_filter = 0;
	}

	filter::filter(filter *next_filter_) {
		next_filter = next_filter_;
	}

	filter::~filter() { }

	void filter::apply_filter(int *buffer_ptr, int w, int h) {
		if (next_filter) {
			next_filter->apply_filter(buffer_ptr, w, h);
		}
	}
}