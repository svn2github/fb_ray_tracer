
#include "light.hpp"

namespace ray_tracer {
	
	light::light() {
		position = point3D();
		diffuse = color_white;
		specular = color_white;
		ambient = color_white;
	}

	light::light(const point3D &position_, const colorRGB &diffuse_, const colorRGB &specular_, const colorRGB &ambient_) {
		position = position_;
		diffuse = diffuse_;
		specular = specular_;
		ambient = ambient_;
	}	
};
