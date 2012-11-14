
#include "misc.hpp"
#include "ray.hpp"
#include "surface_convexhull.hpp"
#include "triangle_hit.hpp"

namespace ray_tracer {

	surface_convexhull::surface_convexhull() { }

	surface_convexhull::surface_convexhull(const std::vector<point3D> &points_) {
		construct(points_);
	}

	void surface_convexhull::construct(const std::vector<point3D> &points_) {
		points = points_;
		faces = convexhull(points).construct_hull();
	}

	double surface_convexhull::hit(const ray &emission_ray, const surface **hit_surface_ptr) const {
		double t = -1, temp_t;
		std::vector<face_t>::const_iterator ret_it = faces.end();

		for (std::vector<face_t>::const_iterator it = faces.begin(); it != faces.end(); ++it) {
			temp_t = triangle_hit(emission_ray, points[std::get<0>(*it)], points[std::get<1>(*it)], points[std::get<2>(*it)]);
			if (temp_t != -1) {
				if (t == -1 || t > temp_t) {
					t = temp_t;
					ret_it = it;
				}
			}
		}
		if (ret_it != faces.end()) {
			surface_triangle *tri_ptr = new surface_triangle(points[std::get<2>(*ret_it)], points[std::get<1>(*ret_it)], points[std::get<0>(*ret_it)]);
			tri_ptr->attach(this);
			*hit_surface_ptr = tri_ptr;
		}
		return t;
	}

	vector3D surface_convexhull::get_normal_vector(const point3D &point) const {
		throw -1;
		return vector3D(0, 0, 0); // Never be here 
	}
}
