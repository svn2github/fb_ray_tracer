#ifndef __SIMPSON_HPP
#define __SIMPSON_HPP

namespace ray_tracer {

	template<class func_obj> 
	class simpson {
	public:
		double integration(double, double, func_obj, double);
	private:
		double sim(double, double, double, double, double);
		double rsim(double, double, double, double, double, double, double);
	private:
		func_obj f;
		double epsilon;
	};

	template<class func_obj>
	double simpson<func_obj>::sim(double l, double r, double lv, double rv, double mv) {
		return (r - l) * (lv + rv + 4 * mv) / 6;
	}

	template<class func_obj>
	double simpson<func_obj>::rsim(double l, double r, double lv, double rv, double mv, double m1v, double m2v) {
		double mid = (l + r) / 2;
		double temp = sim(l, r, lv, rv, mv);
		if (fabs(temp - sim(l, mid, lv, mv, m1v) - sim(mid, r, mv, rv, m2v)) / 15 < epsilon) {
			return temp;
		} else {
			double mid = (l + r) / 2, m1 = (l + (l + r) / 2) / 2, m2 = ((l + r) / 2 + r) / 2;
			return rsim(l, mid, lv, mv, m1v, f((l + m1) / 2), f((m1 + mid) / 2)) + rsim(mid, r, mv, rv, m2v, f((mid + m2) / 2), f((m2 + r) / 2));
		}
	}

	template<class func_obj>
	double simpson<func_obj>::integration(double l, double r, func_obj f_, double epsilon_) {
		f = f_;
		epsilon = epsilon_;
		double mid = (l + r) / 2;
		return rsim(l, r, f(l), f(r), f(mid), f((l + mid) / 2), f((mid + r) / 2));
	}
}

#endif