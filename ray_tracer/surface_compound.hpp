#ifndef __SURFACE_COMPOUND_HPP__
#define __SURFACE_COMPOUND_HPP__

#include <vector>
#include "surface.hpp"

namespace ray_tracer {
	class surface_compound : public surface {
		friend class world;
	public:
		surface_compound();
		double hit(const ray &, const surface **) const;
		void set_material(const material *);
		void set_material(const material *, int);
		colorRGB material_shade(hitInfo *, const colorRGB &, const vector3D &, const vector3D &) const;
		void set_texture(const texture *);
		void set_texture(const texture *, int);
		colorRGB texture_shade(hitInfo *) const;
		void set_twoface_shading(bool);
		void set_twoface_shading(bool, int);
	private:
		std::vector<surface *> surfaces;
	};
}

#endif