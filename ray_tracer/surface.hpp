#ifndef __SURFACE_HPP
#define __SURFACE_HPP

#include "ray.hpp"
#include "vector3D.hpp"
#include "point3D.hpp"
#include "colorRGB.hpp"
#include "hit_record.hpp"

namespace ray_tracer {

	class surface {
	public:
		virtual bool hit(ray *, double, hit_record *) const = 0; // @parameter 3: only hit_t is returned
		virtual vector3D get_normal(point3D *) const = 0;
		virtual void get_color(point3D *, colorRGB *, colorRGB *, colorRGB *) const;
	public:
		// material
		int shininess;
		colorRGB diffuse, specular, ambient;
	};
}

#endif