
#include "surface.hpp"

namespace ray_tracer {

	surface::~surface() { }

	void surface::get_color(const point3D &p_ptr, colorRGB *diffuse_ptr, colorRGB * specular_ptr, colorRGB * ambient_ptr) const {
		*diffuse_ptr = material_ptr->diffuse;
		*specular_ptr = material_ptr->specular;
		*ambient_ptr = material_ptr->ambient;
	}
}
