#ifndef __SURFACE_PLANE_HPP__
#define __SURFACE_PLANE_HPP__

#include "surface.hpp"

namespace ray_tracer {
	class surface_plane : public surface {
	public:
		surface_plane();
		surface_plane(const point3D &, const vector3D &);
		double hit(const ray &) const;
		vector3D get_normal(const point3D &) const;
	private:
		point3D point_on_plane;
		vector3D normal;
	};
}

#endif