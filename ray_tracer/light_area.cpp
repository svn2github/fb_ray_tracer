
#include "light_area.hpp"
#include "world.hpp"

namespace ray_tracer {
	
	const int num_area_sampler = 625;

	light_area::light_area() { 
		radius = 0;
		normal = vector3D();
		axis_u = vector3D();
		axis_v = vector3D();
		smpler = new sampler_jittered;
		smpler->generate(num_area_sampler);
		smpler->map_sample_to_disk();
	}

	light_area::light_area(const point3D &position_, double radius_, const vector3D &normal_, const colorRGB &color_) : light(position_, color_) {
		radius = radius_;
		normal = normal_.normalized();
		axis_u = normal.create_vertical();
		axis_v = normal ^ axis_u;
		smpler = new sampler_jittered;
		smpler->generate(num_area_sampler);
		smpler->map_sample_to_disk();
	}

	light_area::~light_area() {
		delete smpler;
	}

	int light_area::get_sampler_count() const {
		return num_area_sampler;
	}

	point3D light_area::get_light_origin() const {
		point2D p = smpler->get_sampler_zoomed(radius);

		p.x -= radius / 2;
		p.y -= radius / 2;
		return position + axis_u * p.x + axis_v * p.y;
	}
};
