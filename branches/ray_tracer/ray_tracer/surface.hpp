#ifndef __SURFACE_HPP__
#define __SURFACE_HPP__

#include "vector3D.hpp"
#include "point3D.hpp"
#include "colorRGB.hpp"
#include "hitInfo.hpp"
#include "ray.hpp"
#include "material.hpp"
#include "texture.hpp"

namespace ray_tracer {
	class surface {
		friend class tracer;
	public:
		surface();
		virtual ~surface() = 0;
		/** Return a negative value if missed. */
		/** Hit surface pointer remains unchanged if not compound. */
		virtual double hit(const ray &, const surface **) const; 
		virtual vector3D get_normal_vector(const point3D &) const;
		virtual point3D get_local_point(const point3D &) const;
		virtual colorRGB material_shade(hitInfo *, const colorRGB &, const vector3D &, const vector3D &) const;
		virtual void set_material(const material *);
		virtual colorRGB texture_shade(hitInfo *) const;
		virtual void set_texture(const texture *);
		virtual void set_twoface_shading(bool);
	protected:
		const material *material_ptr;
		const texture *texture_ptr;
		bool twoface_shading;
	};
}

#endif