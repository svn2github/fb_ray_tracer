#ifndef __VIEW_PLANE_HPP
#define __VIEW_PLANE_HPP

namespace ray_tracer {
	class view_plane {
	public:
		view_plane();
		view_plane(double, double, double, double);
		double get_left() const;
		void set_left(double);
		double get_right() const;
		void set_right(double);
		double get_top() const;
		void set_top(double);
		double get_bottom() const;
		void set_bottom(double);
		double compute_u(double, double) const;
		double compute_v(double, double) const;
	private:
	private:
		double left, right, top, bottom;
		double delta_u, delta_v;
	};

	inline double view_plane::get_left() const {
		return left;
	}

	inline void view_plane::set_left(double left_) {
		left = left_;
		delta_u = right - left;
	}

	inline double view_plane::get_right() const {
		return right;
	}

	inline void view_plane::set_right(double right_) {
		right = right_;
		delta_u = right - left;
	}

	inline double view_plane::get_top() const {
		return top;
	}

	inline void view_plane::set_top(double top_) {
		top = top_;
		delta_v = top - bottom;
	}

	inline double view_plane::get_bottom() const {
		return bottom;
	}

	inline void view_plane::set_bottom(double bottom_) {
		bottom = bottom_;
		delta_v = top - bottom;
	}

	inline double view_plane::compute_u(double x, double w) const {
		return left + delta_u * x / w;
	}

	inline double view_plane::compute_v(double y, double h) const {
		return bottom + delta_v * y / h;
	}
}

#endif