
#include "camera.hpp"

namespace ray_tracer {

	void camera::compute_axis() {
		axis_w = (eye - lookat).normalized();
		axis_u = up.normalized();
		axis_v = axis_w ^ axis_u;
		dist = (eye - lookat).length();
	}
}