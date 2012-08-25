#ifndef __SURFACE_HPP
#define __SURFACE_HPP

#include "ray.hpp"
#include "vector3D.hpp"
#include "point3D.hpp"

namespace ray_tracer {
	class surface {
	public:
		virtual bool hit(ray *, double *, point3D *) = 0;
		virtual vector3D get_normal(point3D *) = 0;
	public:
		int shininess;
	};

	class surface_sphere : public surface {
	public:
		surface_sphere();
		surface_sphere(const point3D &, double);

		bool hit(ray *, double *, point3D *);
		vector3D get_normal(point3D *);

	public:
		point3D center;
		double radius;
	};

	class surface_plane : public surface {
	public:
		surface_plane();
		surface_plane(const point3D &, const vector3D &);

		bool hit(ray *, double *, point3D *);
		vector3D get_normal(point3D *);

	public:
		point3D point_on_plane;
		vector3D normal;
	};
}

#endif