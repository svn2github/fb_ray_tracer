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
	public:
		surface();
		virtual ~surface() = 0;
		virtual bool two_face() const;
		/** Return a negative value if missed. */
		virtual double hit(const ray &) const; 
		virtual vector3D get_normal(const point3D &) const;
		virtual point3D get_relative_pos(const point3D &) const;
		colorRGB material_shade(hitInfo *, const colorRGB &, const vector3D &, const vector3D &) const;
		void set_material(material *);
		colorRGB texture_shade(hitInfo *) const;
		void set_texture(texture *);
	protected:
		material *material_ptr;
		texture *texture_ptr;
	};

	inline void surface::set_material(material *material_ptr_) {
		material_ptr = material_ptr_;
	}

	inline void surface::set_texture(texture *texture_ptr_) {
		texture_ptr = texture_ptr_;
	}
}

#endif