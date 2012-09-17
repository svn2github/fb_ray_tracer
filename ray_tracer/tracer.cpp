
#include <vector>
#include "light.hpp"
#include "world.hpp"
#include "hitInfo.hpp"
#include "tracer.hpp"
#include "fog.hpp"

namespace ray_tracer {

	colorRGB tracer::ray_color(hitInfo *info_ptr) {
		world *world_ptr;
		vector3D normal, win, wout;
		colorRGB surface_color, light_accumulate, result;
		double temp;

		world_ptr = info_ptr->world_ptr;
		surface_color = info_ptr->surface_ptr->texture_shade(info_ptr);
		win = (info_ptr->emission_ray.get_origin() - info_ptr->hit_point).normalized();
		normal = info_ptr->normal;
		result = info_ptr->world_ptr->get_ambient() * surface_color;
		for (std::vector<light *>::const_iterator iter = world_ptr->get_lights().begin(); iter != world_ptr->get_lights().end(); ++iter) {
			light_accumulate = color_black;
			for (int smpler_cnt = 1; smpler_cnt <= (*iter)->get_sampler_count(); smpler_cnt += 1) {	
				info_ptr->light_position = (*iter)->get_light_origin();
				if ((*iter)->in_range(info_ptr) && !(*iter)->under_shadow(info_ptr)) {
					wout = (info_ptr->light_position - info_ptr->hit_point).normalized();
					temp = fabs(normal * wout); // two side light modeling
					light_accumulate += (*iter)->light_shade(info_ptr) * temp * info_ptr->surface_ptr->material_shade(info_ptr, surface_color, win, wout);
				}
			}
			result += light_accumulate / (*iter)->get_sampler_count();
		}
		result += info_ptr->world_ptr->get_ambient() * surface_color;
		if (world_ptr->get_fog()) {
			result = world_ptr->get_fog()->mix_fog(info_ptr, world_ptr->get_camera()->get_eye(), result);
		}
		return result;
	}
}
