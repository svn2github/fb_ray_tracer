#ifndef __TEXTURE_CHECKER_HPP
#define __TEXTURE_CHECKER_HPP

#include "texture.hpp"

namespace ray_tracer {
	class texture_checker : public texture {
	public:
		texture_checker();
		texture_checker(colorRGB, colorRGB);
		colorRGB texture_shade(hitInfo *) const;
	private:
		colorRGB color1, color2;
	};
}

#endif