#ifndef __RASTER_IMAGE_HPP
#define __RASTER_IMAGE_HPP

#include "vector3D.hpp"
#include "world.hpp"

namespace ray_tracer {

	class raster_image {
	public:
		raster_image();
		raster_image(double, double, double, double);

		// Dimension: pixal
		void fit(int, int, void *);
		void render_scene(world *, ray_tracer *, camera *);

	private:
		ray get_ray(int, int, camera *);

	private:
		double _l, _r, _t, _b;
		int _dest_w, _dest_h, *_pixal_buffer_ptr;
	};
}

#endif