#ifndef __SURFACE_PLANE_HPP
#define __SURFACE_PLANE_HPP

#include "surface.hpp"

namespace ray_tracer {
	class surface_plane : public surface {
	public:
		surface_plane();
		surface_plane(const point3D &, const vector3D &);
		bool hit(const ray &, double, hitInfo *) const;
		vector3D get_normal(const point3D &) const;
	protected:
		point3D point_on_plane;
		vector3D normal;
	};
}

#endif