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
	private:
		double left, right, top, bottom;
	};

	inline double view_plane::get_left() const {
		return left;
	}

	inline void view_plane::set_left(double left_) {
		left = left_;
	}

	inline double view_plane::get_right() const {
		return right;
	}

	inline void view_plane::set_right(double right_) {
		right = right_;
	}

	inline double view_plane::get_top() const {
		return top;
	}

	inline void view_plane::set_top(double top_) {
		top = top_;
	}

	inline double view_plane::get_bottom() const {
		return bottom;
	}

	inline void view_plane::set_bottom(double bottom_) {
		bottom = bottom_;
	}
}

#endif