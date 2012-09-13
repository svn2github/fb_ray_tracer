#ifndef __TEXTURE_IMAGE_HPP
#define __TEXTURE_IMAGE_HPP

#include "texture.hpp"
#include "image.hpp"
#include "image_mapping.hpp"

namespace ray_tracer {
	class texture_image : public texture {
	public:
		texture_image(image *, image_mapping *);
		colorRGB texture_shade(hitInfo *) const;
	private:
		image *image_ptr;
		image_mapping *mapping_ptr;
	};
}

#endif