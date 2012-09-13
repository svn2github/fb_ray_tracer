
#include "ray.hpp"
#include <cmath>
#include "misc.hpp"
#include "surface_triangle.hpp"

namespace ray_tracer {

	surface_triangle::surface_triangle() {
		v0 = point3D();
		v1 = point3D();
		v2 = point3D();
		normal = vector3D();
	}

	surface_triangle::surface_triangle(const point3D &v0_, const point3D &v1_, const point3D &v2_) {
		v0 = v0_;
		v1 = v1_;
		v2 = v2_;
		normal = ((v1 - v0) ^ (v2 - v0)).normalized();
	}

	bool surface_triangle::hit(ray *ray_ptr, double tmin, hitInfo *info_ptr) const {
		double a = v0.x - v1.x, b = v0.x - v2.x, c = ray_ptr->get_dir().x, d = v0.x - ray_ptr->get_origin().x;
		double e = v0.y - v1.y, f = v0.y - v2.y, g = ray_ptr->get_dir().y, h = v0.y - ray_ptr->get_origin().y;
		double i = v0.z - v1.z, j = v0.z - v2.z, k = ray_ptr->get_dir().z, l = v0.z - ray_ptr->get_origin().z;
		double m = f * k - g * j, n = h * k - g * l, p = f * l - h * j;
		double q = g * i - e * k, s = e * j - f * i;
		double inv_deno = 1 / (a * m + b * q + c * s);
		double e1 = d * m - b * n - c * p;
		double beta = e1 * inv_deno;
		if (beta < 0 || beta > 1) {
			return false;
		}
		double r = e * l - h * i;
		double e2 = a * n + d * q + c * r;
		double gamma = e2 * inv_deno;
		if (gamma < 0 || gamma > 1) {
			return false;
		}
		if (gamma + beta > 1) {
			return false;
		}
		double e3 = a * p - b * r + d * s;
		double t = e3 * inv_deno;
		if (t < tmin) {
			return false;
		}
		info_ptr->hit_t = t;
		return true;
	}

	vector3D surface_triangle::get_normal(const point3D &point) const {
		return normal;
	}
}
