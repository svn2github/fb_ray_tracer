#ifndef __CAMERA_HPP
#define __CAMERA_HPP

#include "vector3D.hpp"
#include "point3D.hpp"

namespace ray_tracer {

	class camera {
		friend class raster_image;
	public:
		camera(const point3D &, const vector3D &, const vector3D &);

	protected:	
		camera();

	protected:
		point3D _position;
		vector3D _axis_u, _axis_v, _axis_w;
	};
}

#endif