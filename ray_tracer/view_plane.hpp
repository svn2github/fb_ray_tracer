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
		double get_w() const;
		double get_h() const;
	private:
		double left, right, top, bottom;
		double w, h;
	};

	inline double view_plane::get_left() const {
		return left;
	}

	inline void view_plane::set_left(double left_) {
		left = left_;
		w = right - left;
	}

	inline double view_plane::get_right() const {
		return right;
	}

	inline void view_plane::set_right(double right_) {
		right = right_;
		w = right - left;
	}

	inline double view_plane::get_top() const {
		return top;
	}

	inline void view_plane::set_top(double top_) {
		top = top_;
		h = top - bottom;
	}

	inline double view_plane::get_bottom() const {
		return bottom;
	}

	inline void view_plane::set_bottom(double bottom_) {
		bottom = bottom_;
		h = top - bottom;
	}

	inline double view_plane::compute_u(double x_, double w_) const {
		return left + w * x_ / w_;
	}

	inline double view_plane::compute_v(double y_, double h_) const {
		return bottom + h * y_ / h_;
	}

	inline double view_plane::get_w() const {
		return w;
	}

	inline double view_plane::get_h() const {
		return h;
	}
}

#endif