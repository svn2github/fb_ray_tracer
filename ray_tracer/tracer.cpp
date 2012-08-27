
#include <vector>
#include "light.hpp"
#include "world.hpp"
#include "hit_info.hpp"
#include "tracer.hpp"

namespace ray_tracer {

	colorRGB tracer::ray_color(world *world_ptr, hit_info *info) {
		vector3D n, h, v, l;
		colorRGB Ia, Id, Is;
		colorRGB diffuse, specular, ambient;
		double temp;

		info->surface_ptr->get_color(info->hit_point, &diffuse, &specular, &ambient);
		v = (info->ray_ptr->get_origin() - info->hit_point).normalized();
		n = info->normal;
		for (std::vector<light *>::const_iterator iter = world_ptr->get_lights().begin(); iter != world_ptr->get_lights().end(); ++iter) {
			l = ((*iter)->get_position() - info->hit_point).normalized();
			h = (v + l).normalized();
			temp = n * l;
			if (temp > 0.0) {
				Id += (*iter)->get_color() * diffuse * temp;
			}
			temp = n * h;
			if (temp > 0.0) {
				Is += (*iter)->get_color() * specular * pow(temp, info->surface_ptr->shininess);
			}			
		}
		Ia += info->world_ptr->get_ambient() * ambient;
		return Id + Is + Ia;
	}
}
