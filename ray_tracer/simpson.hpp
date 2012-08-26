#ifndef __SIMPSON_HPP
#define __SIMPSON_HPP

namespace ray_tracer {

	class simpson_func {
	public:
		virtual double operator()(double) const = 0;
	};

	class simpson {
	public:
		double integration(double, double, simpson_func *, double);
	private:
		double sim(double, double, double, double, double);
		double rsim(double, double, double, double, double, double, double);
	private:
		simpson_func *f_ptr;
		double epsilon;
	};
}

#endif