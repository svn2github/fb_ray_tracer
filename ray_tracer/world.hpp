#ifndef __WOLRD_HPP
#define __WOLRD_HPP

#include <vector>
#include "light.hpp"
#include "surface.hpp"
#include "camera.hpp"

namespace ray_tracer {

	class world {
		friend class raster_image;
		friend class ray_tracer;

	public:
		world();
		~world();
		void add_light(light *);
		void add_surface(surface *);
		void set_camera(camera *);
		void set_raster_image(raster_image *);
		void fit_window(int, int, void *); // Dimension: pixal
		void render_scene();		
		
	private:
		std::vector<light *> lights_ptr;
		std::vector<surface *> surfaces_ptr;
		camera *camera_ptr;
		raster_image *image_ptr;
		ray_tracer *tracer_ptr;
		int dest_w, dest_h, *pixal_buffer_ptr;
	};
}

#endif