
#include "camera.hpp"

namespace ray_tracer {

	camera::camera() { 
		position = point3D();
		axis_w = vector3D();
		axis_u = vector3D();
		axis_v = vector3D();
	}

	camera::camera(const point3D &position_, const vector3D &axis_w_, const vector3D &axis_u_) {
		position = position_;
		axis_w = axis_w_.normalized();
		axis_u = axis_u_.normalized();
		axis_v = axis_w ^ axis_u;
	}
}