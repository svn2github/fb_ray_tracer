
#include <vector>
#include "light.hpp"
#include "world.hpp"
#include "hitInfo.hpp"
#include "tracer.hpp"

namespace ray_tracer {

	colorRGB tracer::ray_color(hitInfo *info_ptr) {
		world *world_ptr;
		vector3D normal, win, wout;
		colorRGB surface_color, result;
		double temp;

		world_ptr = info_ptr->world_ptr;
		surface_color = info_ptr->surface_ptr->texture_shade(info_ptr);
		win = (info_ptr->ray_ptr->get_origin() - info_ptr->hit_point).normalized();
		normal = info_ptr->normal;
		result = info_ptr->world_ptr->get_ambient() * surface_color;
		for (std::vector<light *>::const_iterator iter = world_ptr->get_lights().begin(); iter != world_ptr->get_lights().end(); ++iter) {
			if ((*iter)->in_range(info_ptr) && !(*iter)->under_shadow(info_ptr)) {
				wout = ((*iter)->get_position() - info_ptr->hit_point).normalized();
				temp = fabs(normal * wout); // two side light modeling
				result += (*iter)->light_shade(info_ptr) * temp * info_ptr->surface_ptr->material_shade(info_ptr, surface_color, win, wout);
			}
		}
		result += info_ptr->world_ptr->get_ambient() * surface_color;
		return result;
	}
}
