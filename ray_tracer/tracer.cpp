
#include <vector>
#include "light.hpp"
#include "world.hpp"
#include "hit_info.hpp"
#include "tracer.hpp"

namespace ray_tracer {

	colorRGB tracer::ray_color(hit_info *info) {
		world *world_ptr;
		vector3D normal, win, wout;
		colorRGB surface_color, result;
		double temp;

		world_ptr = info->world_ptr;
		info->surface_ptr->get_color(info->hit_point, &surface_color);
		win = (info->ray_ptr->get_origin() - info->hit_point).normalized();
		normal = info->normal;
		result = info->world_ptr->get_ambient() * surface_color;
		for (std::vector<light *>::const_iterator iter = world_ptr->get_lights().begin(); iter != world_ptr->get_lights().end(); ++iter) {
			if ((*iter)->under_shadow(info) == false) {
				wout = ((*iter)->get_position() - info->hit_point).normalized();
				temp = normal * wout;
				if (temp > 0) {
					result += (*iter)->get_color() * temp * info->surface_ptr->get_material()->material_shade(info, surface_color, win, wout);
				}
			}
		}
		result += info->world_ptr->get_ambient() * surface_color;
		return result;
	}
}
