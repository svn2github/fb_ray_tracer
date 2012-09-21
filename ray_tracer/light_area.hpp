#ifndef __LIGHT_AREA_HPP
#define __LIGHT_AREA_HPP

#include "light.hpp"
#include "sampler_jittered.hpp"

namespace ray_tracer {
	class light_area : public light {
	public:
		light_area();
		light_area(const point3D &, const colorRGB &, bool, double, const vector3D &);
		~light_area();
		int get_sampler_count() const;
		point3D get_light_origin() const;
	private:
		sampler_jittered *smpler;
		double radius;
		vector3D normal, axis_u, axis_v;
	};
}

#endif