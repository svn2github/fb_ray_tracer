
#include <vector>
#include "light.hpp"
#include "world.hpp"
#include "hitInfo.hpp"
#include "tracer.hpp"

namespace ray_tracer {

	colorRGB tracer::ray_color(hitInfo *info) {
		world *world_ptr;
		vector3D normal, win, wout;
		colorRGB surface_color, result;
		double temp;

		world_ptr = info->world_ptr;
		surface_color = info->surface_ptr->texture_shade(info);
		win = (info->ray_ptr->get_origin() - info->hit_point).normalized();
		normal = info->normal;
		result = info->world_ptr->get_ambient() * surface_color;
		for (std::vector<light *>::const_iterator iter = world_ptr->get_lights().begin(); iter != world_ptr->get_lights().end(); ++iter) {
			if ((*iter)->under_shadow(info) == false) {
				wout = ((*iter)->get_position() - info->hit_point).normalized();
				temp = fabs(normal * wout); // two side light modeling
				result += (*iter)->get_color() * temp * info->surface_ptr->material_shade(info, surface_color, win, wout);
			}
		}
		result += info->world_ptr->get_ambient() * surface_color;
		return result;
	}
}
