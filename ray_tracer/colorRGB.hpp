#ifndef __COLORRGB_HPP
#define __COLORRGB_HPP

namespace ray_tracer {
	class colorRGB {
	public:
		colorRGB();
		colorRGB(double, double, double);
		int clamp_to_int() const;
		friend colorRGB operator+(const colorRGB &, const colorRGB &);
		friend colorRGB &operator+=(colorRGB &, const colorRGB &);
		friend colorRGB operator*(const colorRGB &, double);
		friend colorRGB operator*(double, const colorRGB &);
		friend colorRGB operator*(const colorRGB &, const colorRGB &);
	public:
		double r, g, b;
	};

	inline int colorRGB::clamp_to_int() const {
		int r_ = (int)((r > 1.0f ? 1.0f : r) * 255);
		int g_ = (int)((g > 1.0f ? 1.0f : g) * 255);
		int b_ = (int)((b > 1.0f ? 1.0f : b) * 255);

		return (b_ | (g_ << 8) | (r_ << 16));
	}

	inline colorRGB operator+(const colorRGB &c1, const colorRGB &c2) {
		return colorRGB(c1.r + c2.r, c1.g + c2.g, c1.b + c2.b);
	}

	inline colorRGB &operator+=(colorRGB &c1, const colorRGB &c2) {
		c1.r += c2.r;
		c1.g += c2.g;
		c1.b += c2.b;
		return c1;
	}
	
	inline colorRGB operator*(const colorRGB &c, double f) {
		return colorRGB(c.r * f, c.g * f, c.b * f);
	}

	inline colorRGB operator*(double f, const colorRGB &c) {
		return colorRGB(c.r * f, c.g * f, c.b * f);
	}

	inline colorRGB operator*(const colorRGB &c1, const colorRGB &c2) {
		return colorRGB(c1.r * c2.r, c1.g * c2.g, c1.b * c2.b);
	}

	extern colorRGB color_black;
	extern colorRGB color_white;
	extern colorRGB color_red;
	extern colorRGB color_green;
	extern colorRGB color_blue;
}

#endif