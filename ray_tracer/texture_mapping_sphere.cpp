
#include "texture_mapping_sphere.hpp"

namespace ray_tracer {

	point2D texture_mapping_sphere::get_coordinate(hitInfo *info_ptr) const {
		point3D p = info_ptr->hit_relative_point;
		double alpha, beta;

		p = p.to_vector().normalized().to_point();
		alpha = acos(p.z), beta = atan2(p.x, p.y);
		if (beta < 0) {
			beta += pi * 2;
		}
		return point2D(beta / 2 / pi, alpha / pi);
	}
}