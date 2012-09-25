
#include "camera.hpp"
#include "hitInfo.hpp"
#include "matrix3D.hpp"
#include "world.hpp"
#include "misc.hpp"
#include <cassert>

namespace ray_tracer {

	camera::camera() {
		eye = point3D(0, 0, 0);
		lookat = point3D(0, 0, 1);
		up = vector3D(0, 1, 0);
		compute_axis();
	}

	camera::camera(const point3D &eye_, const point3D &lookat_, const vector3D &up_) {
		eye = eye_;
		lookat = lookat_;
		up = up_;
		compute_axis();
	}
	
	camera::~camera() { }

	colorRGB camera::render_scene(const point3D &origin, const vector3D &dir, world *world_ptr) {
		hitInfo info;

		info.camera_ptr = this;
		if (world_ptr->get_hit(ray(origin, dir), &info)) {
			return world_ptr->get_tracer()->ray_color(&info);
		} else {
			return world_ptr->get_background();
		}
	}

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

	/** Note: axis_w dot axis_v = 0 */
	void camera::compute_axis() {
		axis_w = (eye - lookat).normalized();
		axis_v = -up.normalized();
		assert(dblcmp(axis_w * axis_v) == 0);
		axis_u = axis_v ^ axis_w;
	}
}