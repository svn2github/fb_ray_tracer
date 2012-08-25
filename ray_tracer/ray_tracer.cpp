
#include "world.hpp"
#include "ray_tracer.hpp"
#include <vector>

namespace ray_tracer {

	colorRGB ray_tracer::ray_color(world *world_ptr, hit_record *record) {
		vector3D n, h, v, l;
		colorRGB Ia, Id, Is;
		v = (record->ray_ptr->start - record->hit_point).normalized();
		n = record->normal;;
		for (std::vector<light *>::iterator iter = world_ptr->lights_ptr.begin(); iter != world_ptr->lights_ptr.end(); ++iter) {
			l = ((*iter)->position - record->hit_point).normalized();
			h = (v + l).normalized();
			Id += (*iter)->color * record->surface_ptr->diffuse * max(0.0, n * l);
			Is += (*iter)->color * record->surface_ptr->specular * pow(max(0.0, n * h), record->surface_ptr->shininess);
			Ia += (*iter)->color * record->surface_ptr->ambient;
		}
		return Id + Is + Ia;
	}
}
