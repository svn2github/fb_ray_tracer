
#include "world.hpp"
#include "ray_tracer.hpp"
#include <vector>

namespace ray_tracer {

	colorRGB ray_tracer::ray_color(world *world_ptr, hit_record *record) {
		vector3D n, h, v, l;
		colorRGB Ia, Id, Is;
		colorRGB diffuse, specular, ambient;

		record->surface_ptr->get_color(&record->hit_point, &diffuse, &specular, &ambient);
		v = (record->ray_ptr->get_origin() - record->hit_point).normalized();
		n = record->normal;
		for (std::vector<light *>::iterator iter = world_ptr->lights.begin(); iter != world_ptr->lights.end(); ++iter) {
			l = ((*iter)->get_position() - record->hit_point).normalized();
			h = (v + l).normalized();
			Id += (*iter)->get_color() * diffuse * max(0.0, n * l);
			Is += (*iter)->get_color() * specular * pow(max(0.0, n * h), record->surface_ptr->shininess);
			Ia += (*iter)->get_color() * ambient;
		}
		return Id + Is + Ia;
	}
}
