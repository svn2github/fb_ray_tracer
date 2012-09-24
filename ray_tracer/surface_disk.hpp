#ifndef __SURFACE_DISK_HPP
#define __SURFACE_DISK_HPP

#include "surface.hpp"

namespace ray_tracer {
	class surface_disk : public surface {
	public:
		surface_disk();
		surface_disk(const point3D &, const vector3D &, double);
		bool hit(const ray &, double, hitInfo *) const;
		vector3D get_normal(const point3D &) const;
	private:
		point3D center;
		vector3D normal;
		double radius, radius_squared;
	};
}

#endif