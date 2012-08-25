
#include "world.hpp"
#include "ray_tracer.hpp"
#include <vector>

namespace ray_tracer {

	bool ray_tracer::ray_color(raster_image *image, world *world, surface *surface, ray *ray, colorRGB *color) {
		point3D contact_point;

		if (!surface->hit(ray, 0, &contact_point)) {
			return false;
		} else {
			vector3D n, h, v, l;
			colorRGB Ia, Id, Is;
			v = (ray->start - contact_point).normalized();
			n = surface->get_normal(&contact_point);
			for (std::vector<light *>::iterator iter = world->lights_ptr.begin(); iter != world->lights_ptr.end(); ++iter) {
				l = ((*iter)->position - contact_point).normalized();
				h = (v + l).normalized();
				Id += (*iter)->diffuse * max(0.0, n * l);
				Is += (*iter)->specular * pow(max(0.0, n * h), surface->shininess);
				Ia += (*iter)->ambient;
			}
			*color = Id + Is + Ia;
			return true;
		}
	}
}
