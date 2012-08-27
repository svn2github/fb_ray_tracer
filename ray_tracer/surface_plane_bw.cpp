
// This class is just for test

#include "surface_plane.hpp"

namespace ray_tracer {

	surface_plane_bw::surface_plane_bw() {
		set_point_on_plane(point3D());
		set_normal(vector3D());
	}

	surface_plane_bw::surface_plane_bw(const point3D &point_, const vector3D &normal_) {
		set_point_on_plane(point_);
		set_normal(normal_);
	}

	// Hack implementation
	void surface_plane_bw::get_color(const point3D &p, colorRGB *diffuse_ptr, colorRGB * specular_ptr, colorRGB * ambient_ptr) const {
		int y = (p.y + 100000) / 3, z = (p.z + 100000) / 3;
	
		if ((y + z) & 1) {
			*diffuse_ptr = color_black;
		} else {
			*diffuse_ptr = color_white;
		}		
		*specular_ptr = color_black;
		*ambient_ptr = color_black;
	}
}

