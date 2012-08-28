#ifndef __SURFACE_HPP
#define __SURFACE_HPP

#include "vector3D.hpp"
#include "point3D.hpp"
#include "colorRGB.hpp"
#include "hit_info.hpp"
#include "ray.hpp"

namespace ray_tracer {
	class surface {
	public:
		/** parameter 3: only hit_t is returned */
		virtual bool hit(ray *, double, hit_info *) const = 0; 
		virtual vector3D get_normal(const point3D &) const = 0;
		virtual void get_color(const point3D &, colorRGB *, colorRGB *, colorRGB *) const;
	public:
		// material
		int shininess;
		colorRGB diffuse, specular, ambient;
	};
}

#endif