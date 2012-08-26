
#include "simpson.hpp"
#include <cmath>

namespace ray_tracer {

	inline double simpson::sim(double l, double r, double lv, double rv, double mv) {
		return (r - l) * (lv + rv + 4 * mv) / 6;
	}

	double simpson::rsim(double l, double r, double lv, double rv, double mv, double m1v, double m2v) {
		double mid = (l + r) / 2;
		double temp = sim(l, r, lv, rv, mv);
		if (fabs(temp - sim(l, mid, lv, mv, m1v) - sim(mid, r, mv, rv, m2v)) / 15 < epsilon) {
			return temp;
		} else {
			double mid = (l + r) / 2, m1 = (l + (l + r) / 2) / 2, m2 = ((l + r) / 2 + r) / 2;
			return rsim(l, mid, lv, mv, m1v, (* f_ptr)((l + m1) / 2), (* f_ptr)((m1 + mid) / 2)) + rsim(mid, r, mv, rv, m2v, (* f_ptr)((mid + m2) / 2), (* f_ptr)((m2 + r) / 2));
		}
	}

	double simpson::integration(double l, double r, simpson_func *f_ptr_, double epsilon_) {
		f_ptr = f_ptr_;
		epsilon = epsilon_;
		double mid = (l + r) / 2;
		return rsim(l, r, (* f_ptr)(l), (* f_ptr)(r), (* f_ptr)(mid), (* f_ptr)((l + mid) / 2), (* f_ptr)((mid + r) / 2));
	}
}