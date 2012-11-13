
#include "misc.hpp"
#include "ray.hpp"
#include "surface_compound.hpp"

namespace ray_tracer {

	surface_compound::surface_compound() { }
	
	void surface_compound::add_surface(surface *surface_) {
		surfaces.push_back(surface_);
	}

	/** material/texture shade: No defination */
	colorRGB surface_compound::material_shade(hitInfo *info_ptr, const colorRGB &surface_color, const vector3D &win, const vector3D &wout) const {
		return color_black;
	}

	colorRGB surface_compound::texture_shade(hitInfo *info_ptr) const {
		return color_black;
	}
	/** = */

	void surface_compound::set_material(const material *material_ptr_) {
		for (std::vector<surface *>::const_iterator iter = surfaces.begin(); iter != surfaces.end(); ++iter) {
			(*iter)->set_material(material_ptr_);
		}
	}

	void surface_compound::set_material(const material *material_ptr_, int index_) {
		surfaces[index_]->set_material(material_ptr_);
	}

	void surface_compound::set_texture(const texture *texture_ptr_) {
		for (std::vector<surface *>::const_iterator iter = surfaces.begin(); iter != surfaces.end(); ++iter) {
			(*iter)->set_texture(texture_ptr_);
		}
	}
	
	void surface_compound::set_texture(const texture *texture_ptr_, int index_) {
		surfaces[index_]->set_texture(texture_ptr_);
	}

	void surface_compound::set_twoface_shading(bool twoface_) {
		for (std::vector<surface *>::const_iterator iter = surfaces.begin(); iter != surfaces.end(); ++iter) {
			(*iter)->set_twoface_shading(twoface_);
		}
	}

	void surface_compound::set_twoface_shading(bool twoface_, int index_) {
		surfaces[index_]->set_twoface_shading(twoface_);
	}

	double surface_compound::hit(const ray &emission_ray, const surface **hit_surface_ptr) const {
		bool hit_flag = false;
		double hit_time = huge_double;
		const surface *surface_ptr, *temp_surface_ptr;

		for (std::vector<surface *>::const_iterator iter = surfaces.begin(); iter != surfaces.end(); ++iter) {
			surface_ptr = *iter;
			temp_surface_ptr = NULL;

			double t = surface_ptr->hit(emission_ray, &temp_surface_ptr);

			if (temp_surface_ptr != NULL) surface_ptr = temp_surface_ptr;
			/* Avoid hiting the surface which shots this ray. */
			if (t > epsilon && t < hit_time) {
				hit_time = t;
				*hit_surface_ptr = surface_ptr;
				hit_flag = true;
			}
		}
		return hit_flag ? hit_time : -1;
	}
}
