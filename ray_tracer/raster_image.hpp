#ifndef __RASTER_IMAGE_HPP
#define __RASTER_IMAGE_HPP

namespace ray_tracer {
	class raster_image {
	public:
		raster_image();
		raster_image(double, double, double, double);
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

	inline double raster_image::get_left() const {
		return left;
	}

	inline void raster_image::set_left(double left_) {
		left = left_;
	}

	inline double raster_image::get_right() const {
		return right;
	}

	inline void raster_image::set_right(double right_) {
		right = right_;
	}

	inline double raster_image::get_top() const {
		return top;
	}

	inline void raster_image::set_top(double top_) {
		top = top_;
	}

	inline double raster_image::get_bottom() const {
		return bottom;
	}

	inline void raster_image::set_bottom(double bottom_) {
		bottom = bottom_;
	}
}

#endif