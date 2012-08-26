
#include "surface.hpp"

namespace ray_tracer {

	void surface::get_color(point3D *p_ptr, colorRGB *diffuse_ptr, colorRGB * specular_ptr, colorRGB * ambient_ptr) const {
		*diffuse_ptr = diffuse;
		*specular_ptr = specular;
		*ambient_ptr = ambient;
	}
}
