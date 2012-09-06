
#include "camera.hpp"
#include "matrix3D.hpp"
#include <cmath>

namespace ray_tracer {

	camera::~camera() { }

	void camera::rotate(double angle) {
		matrix3D mat1, mat2, mat3, mat;

		mat1.value[0][0] = axis_u.x;
		mat1.value[0][1] = axis_v.x;
		mat1.value[0][2] = axis_w.x;
		mat1.value[1][0] = axis_u.y;
		mat1.value[1][1] = axis_v.y;
		mat1.value[1][2] = axis_w.y;
		mat1.value[2][0] = axis_u.z;
		mat1.value[2][1] = axis_v.z;
		mat1.value[2][2] = axis_w.z;
		mat2.value[0][0] = cos(angle);
		mat2.value[0][1] = -sin(angle);
		mat2.value[1][0] = sin(angle);
		mat2.value[1][1] = cos(angle);
		mat2.value[2][2] = 1;
		mat3 = mat1.transpose();
		mat = mat1 * mat2 * mat3;
		axis_u = mat * axis_u;
		axis_v = mat * axis_v;
		axis_w = mat * axis_w;
		up = mat * up;
	}

	void camera::compute_axis() {
		axis_w = (eye - lookat).normalized();
		axis_v = -up;
		axis_u = axis_v ^ axis_w;
	}
}