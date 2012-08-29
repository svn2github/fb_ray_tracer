
#include "camera.hpp"

namespace ray_tracer {

	camera::~camera() { }

	void camera::compute_axis() {
		axis_w = (eye - lookat).normalized();
		axis_v = -up.normalized();
		axis_u = axis_v ^ axis_w;
	}
}