
#include "filter.hpp"

namespace ray_tracer {
	
	filter::~filter() { }

	void filter::apply_filter(int *buffer_ptr, int w, int h) {
		if (next_filter) {
			next_filter->apply_filter(buffer_ptr, w, h);
		}
	}
}