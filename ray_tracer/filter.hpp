#ifndef __FILTER_HPP
#define __FILTER_HPP

namespace ray_tracer {
	class filter {
	public:
		filter();
		filter(filter *);
		virtual ~filter() = 0;
		virtual void apply_filter(int *, int, int) = 0;
	protected:
		filter *next_filter;
	};
}

#endif