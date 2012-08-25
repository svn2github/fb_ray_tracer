
// This class is just for test

#include "surface.hpp"

namespace ray_tracer {

	surface_plane_bw::surface_plane_bw() {
		point_on_plane = point3D();
		normal = vector3D();
	}

	surface_plane_bw::surface_plane_bw(const point3D &point_, const vector3D &normal_) {
		point_on_plane = point_;
		normal = normal_;
	}

	// Hack implementation
	void surface_plane_bw::get_color(point3D *p_ptr, colorRGB *diffuse_ptr, colorRGB * specular_ptr, colorRGB * ambient_ptr) {
		int y = (p_ptr->y + 100000) / 3, z = (p_ptr->z + 100000) / 3;
	
		if ((y + z) & 1) {
			*diffuse_ptr = color_black;
		} else {
			*diffuse_ptr = color_white;
		}		
		*specular_ptr = color_black;
		*ambient_ptr = color_black;
	}
}
