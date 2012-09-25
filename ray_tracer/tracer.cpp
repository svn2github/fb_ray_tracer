
#include <vector>
#include "light.hpp"
#include "world.hpp"
#include "hitInfo.hpp"
#include "tracer.hpp"
#include "fog.hpp"

namespace ray_tracer {

	colorRGB tracer::ray_color(hitInfo *info_ptr) {
		if (info_ptr->ray_tracing_depth == 0) {
			return color_black;
		} else {
			world *world_ptr;
			vector3D normal, win, wout;
			colorRGB surface_color, result;
			double temp;

			world_ptr = info_ptr->world_ptr;
			surface_color = info_ptr->surface_ptr->texture_shade(info_ptr);
			win = (info_ptr->emission_ray.get_origin() - info_ptr->hit_point).normalized();
			normal = info_ptr->normal;
			result = info_ptr->world_ptr->get_ambient() * surface_color;
			for (std::vector<light *>::const_iterator iter = world_ptr->get_lights().begin(); iter != world_ptr->get_lights().end(); ++iter) {
				info_ptr->light_position = (*iter)->get_light_origin(info_ptr);
				if ((*iter)->in_range(info_ptr) && !(*iter)->under_shadow(info_ptr)) {
					wout = (info_ptr->light_position - info_ptr->hit_point).normalized();
					temp = normal * wout; 
					if (temp > 0) {
						result += (*iter)->light_shade(info_ptr) * temp * info_ptr->surface_ptr->material_shade(info_ptr, surface_color, win, wout);
					}
				}
			}
			result += info_ptr->world_ptr->get_ambient() * surface_color;
			if (world_ptr->get_fog()) {
				result = world_ptr->get_fog()->fog_blending(info_ptr, world_ptr->get_camera()->get_origin(), result);
			}
			return result;
		}
	}
}
