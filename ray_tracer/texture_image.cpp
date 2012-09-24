
#include "texture_image.hpp"
#include <cstdio>

namespace ray_tracer {

	texture_image::texture_image(image *image_ptr_, texture_mapping *mapping_ptr_) {
		image_ptr = image_ptr_;
		mapping_ptr = mapping_ptr_;
	}

	colorRGB texture_image::texture_shade(hitInfo *info_ptr) const {
		point2D coord = mapping_ptr->get_coordinate(info_ptr);
		int x, y;

		x = (int)((image_ptr->get_w() - 1) * coord.x);
		y = (int)((image_ptr->get_h() - 1) * coord.y);
		return image_ptr->get_color(x, y);
	}
}
