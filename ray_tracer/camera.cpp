
#include "camera.hpp"

namespace ray_tracer {

	camera::camera() { 
		_position = point3D();
		_axis_w = _axis_u = _axis_v = vector3D();
	}

	camera::camera(const point3D &position_, const vector3D &axis_w_, const vector3D &axis_u_) {
		_position = position_;
		_axis_w = axis_w_.normalized();
		_axis_u = axis_u_.normalized();
		_axis_v = _axis_w ^ _axis_u;
	}
}