#ifndef __SURFACE_HPP
#define __SURFACE_HPP

#include "vector3D.hpp"
#include "point3D.hpp"
#include "colorRGB.hpp"
#include "hit_info.hpp"
#include "ray.hpp"
#include "material.hpp"

namespace ray_tracer {
	class surface {
	public:
		/** parameter 3: only hit_t is returned */
		virtual bool hit(ray *, double, hit_info *) const = 0; 
		virtual vector3D get_normal(const point3D &) const = 0;
		virtual void get_color(const point3D &, colorRGB *, colorRGB *, colorRGB *) const;
		material *get_material() const;
		void set_material(material *);
	private:
		material *material_ptr;
	};

	inline material *surface::get_material() const {
		return material_ptr;
	}

	inline void surface::set_material(material *material_ptr_) {
		material_ptr = material_ptr_;
	}
}

#endif