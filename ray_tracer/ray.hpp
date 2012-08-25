#ifndef __RAY_HPP
#define __RAY_HPP

#include "vector3D.hpp"
#include "point3D.hpp"

namespace ray_tracer {

	class ray {
	public:
		ray();
		ray(const point3D &, const vector3D &);

	public:
		point3D start;
		vector3D dir;
	};
}

#endif