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
		virtual double hit(const ray &) const; 
		virtual vector3D get_normal_vector(const point3D &) const;
		virtual point3D get_local_point(const point3D &) const;
		void enable_twoface_shading(bool);
		colorRGB material_shade(hitInfo *, const colorRGB &, const vector3D &, const vector3D &) const;
		void set_material(material *);
		colorRGB texture_shade(hitInfo *) const;
		void set_texture(texture *);
	protected:
		material *material_ptr;
		texture *texture_ptr;
	private:
		bool twoface_shading;
	};

	inline void surface::set_material(material *material_ptr_) {
		material_ptr = material_ptr_;
	}

	inline void surface::set_texture(texture *texture_ptr_) {
		texture_ptr = texture_ptr_;
	}
}

#endif