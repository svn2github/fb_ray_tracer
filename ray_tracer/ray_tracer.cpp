
#include "world.hpp"
#include "ray_tracer.hpp"
#include <vector>

namespace ray_tracer {

	colorRGB ray_tracer::ray_color(world *world_ptr, surface *surface_ptr, ray *ray_ptr, point3D *contact_point_ptr) {
		vector3D n, h, v, l;
		colorRGB Ia, Id, Is;
		v = (ray_ptr->start - *contact_point_ptr).normalized();
		n = surface_ptr->get_normal(contact_point_ptr);
		for (std::vector<light *>::iterator iter = world_ptr->lights_ptr.begin(); iter != world_ptr->lights_ptr.end(); ++iter) {
			l = ((*iter)->position - *contact_point_ptr).normalized();
			h = (v + l).normalized();
			Id += (*iter)->diffuse * max(0.0, n * l);
			Is += (*iter)->specular * pow(max(0.0, n * h), surface_ptr->shininess);
			Ia += (*iter)->ambient;
		}
		return Id + Is + Ia;
	}
}
