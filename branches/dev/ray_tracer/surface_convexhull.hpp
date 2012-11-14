#ifndef __SURFACE_CONVEXHULL_HPP__
#define __SURFACE_CONVEXHULL_HPP__

#include "surface.hpp"
#include "surface_triangle.hpp"
#include "convexhull.hpp"
#include <vector>

namespace ray_tracer {
	class surface_convexhull : public surface {
	public:
		surface_convexhull(const std::vector<point3D> &);
		double hit(const ray &, const surface **) const;
		vector3D get_normal_vector(const point3D &) const;
	protected:
		surface_convexhull();
		void construct(const std::vector<point3D> &);
	protected:
		std::vector<point3D> points;
		std::vector<face_t> faces;
		std::vector<surface_triangle> face_tris;
	};
}

#endif
