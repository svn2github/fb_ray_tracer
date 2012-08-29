
#include <cmath>
#include "misc.hpp"
#include "ray.hpp"
#include "surface_plane.hpp"

namespace ray_tracer {

	surface_plane::surface_plane() {
		set_point_on_plane(point3D());
		set_normal(vector3D());
	}

	surface_plane::surface_plane(const point3D &point_, const vector3D &normal_) {
		set_point_on_plane(point_);
		set_normal(normal_);
	}

	bool surface_plane::hit(ray *ray_ptr, double tmin, hit_info *hit_ptr) const {
		double deno = normal * ray_ptr->get_dir();
		double t = (point_on_plane - ray_ptr->get_origin()) * normal / deno;
		
		if (dblcmp(deno) == 0 || t < tmin) {
			return false;
		}
		hit_ptr->hit_t = t;
		return true;
	}

	vector3D surface_plane::get_normal(const point3D &point) const {
		return normal;
	}
	
	// This class is just for test
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
		const int sz = 4;
		const double huge = 10000;
		int x = (p.x + huge) / sz, y = (p.y + huge) / sz, z = (p.z + huge) / sz, mod;
	
		mod = (((x + y + z) % 2) + 2) % 2;
		if (mod) {
			*diffuse_ptr = color_black;
			*ambient_ptr = color_black;
		} else {
			*diffuse_ptr = color_white;
			*ambient_ptr = color_white;
		}		
		*specular_ptr = color_black;
	}

}
