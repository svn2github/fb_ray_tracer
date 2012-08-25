
#include "world.hpp"
#include "ray_tracer.hpp"
#include <vector>

namespace ray_tracer {

	bool ray_tracer::ray_color(world *world_ptr, surface *surface_ptr, ray *ray_ptr, colorRGB *color_ptr) {
		point3D contact_point;

		if (!surface_ptr->hit(ray_ptr, 0, &contact_point)) {
			return false;
		} else {
			vector3D n, h, v, l;
			colorRGB Ia, Id, Is;
			v = (ray_ptr->start - contact_point).normalized();
			n = surface_ptr->get_normal(&contact_point);
			for (std::vector<light *>::iterator iter = world_ptr->lights_ptr.begin(); iter != world_ptr->lights_ptr.end(); ++iter) {
				l = ((*iter)->position - contact_point).normalized();
				h = (v + l).normalized();
				Id += (*iter)->diffuse * max(0.0, n * l);
				Is += (*iter)->specular * pow(max(0.0, n * h), surface_ptr->shininess);
				Ia += (*iter)->ambient;
			}
			*color_ptr = Id + Is + Ia;
			return true;
		}
	}
}
