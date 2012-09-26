
#include "BRDF_mirror.hpp"
#include "light_point.hpp"
#include "vector3D.hpp"
#include "misc.hpp"
#include "world.hpp"

namespace ray_tracer {

	colorRGB BRDF_mirror::f(hitInfo *info_ptr, const vector3D &win, const vector3D &wout) const {
		return coefficient;
	}

	colorRGB BRDF_mirror::reflect_f(hitInfo *info_ptr, const vector3D &win) const {
		hitInfo info = *info_ptr;
		light_point reflect = light_point(info_ptr->hit_point, coefficient);

		reflect.inherit_light(info_ptr->light_ptr);
		// info.world_ptr = info_ptr->world_ptr;
		// info.sampler_iterator_ptr = info_ptr->sampler_iterator_ptr;
		info.ray_tracing_depth = info_ptr->ray_tracing_depth - 1;
		return coefficient * info_ptr->camera_ptr->render_scene(info_ptr->hit_point, 2 * info_ptr->normal - win, &info, &reflect);
	}
}
